function pso=init_PSOwHF(board,csrn),
% init_PSOwHF        Initialize PSO (Particle Swarm Intelligence)
%                    with Hidden-layer Feedback
%
% Velocity update equation 
% The velocity update equation (1) is comprised of:
%    inertia of the previous velocity, 
%    the cognitive acceleration term, and 
%    the social acceleration term. 
% This velocity is moving towards both to the local best of the given particle and the global best positions of the whole population. 
%
% The location update equation (2) updates the location of the given particle using the velocity update equation.
%
% P/p   particle
% G/g   global
% L/l   location
% V/v   velocity
% Hierarchy of the variables
% pso
%       .cfg    (Configuration)
%           .particle
%               .associate
%       .particle
%           .associate
%
% Hierarchy
%   node        A node corresponds to a SNR and multiple particles are
%               employed to find the best solution for the node
%   particle    A particle leads many associates that help the particle
%               find the solution
%   associate   A associate 
% On all three levels, the goal is shared. In other words, the target
% fitness is identical.
%
% Associate
% http://dictionary.reference.com/browse/associate
% 1. to connect or bring into relation, as thought, feeling,memory, etc.
% 2. to join as a companion, partner, or ally 
% 3. to unite; combine 
% 7. a person who shares actively in anything as a business, enterprise, or
% undertaking; partner; colleague 
% 8. a companion or comrade 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         pso.cfg.p(article)        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% There is only one particle for 2x2 using symmetry.
[row_W_u,clmn_W_u] = size( csrn.srn.W_u );
[row_W_h,clmn_W_h] = size( csrn.srn.W_h );
[row_W_v,clmn_W_v] = size( csrn.srn.W_v );

pso.cfg.p.d=row_W_u.*clmn_W_u+row_W_h.*clmn_W_h+row_W_v.*clmn_W_v;   % dimension
pso.cfg.p.size=20;                   % Number of particles        
pso.cfg.p.w=0.8;
pso.cfg.p.c1=2;
pso.cfg.p.c2=2;
pso.cfg.p.l_id_max=2.0;
pso.cfg.p.v_id_max=100;
pso.cfg.p.target_fitness=0;           % Number of acceptable errors
% Global fitness
% An arbitrary number large enough to update the global best at the
% beginning of the iteration. The following condition is in mind.
% if ( pso.cfg.p.g_fitness > min(pso.p.P_fitness) )
pso.cfg.p.g_fitness = 10^13;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      pso.cfg.p.a(ssociate)        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.cfg.a.d=row_W_h.*clmn_W_h;      % dimension
pso.cfg.a.size=10;                 % Number of associates per particle
pso.cfg.a.w=0.2;
pso.cfg.a.c1=1;
pso.cfg.a.c2=1;
pso.cfg.a.target_fitness=pso.cfg.p.target_fitness;
pso.cfg.a.g_fitness=pso.cfg.p.g_fitness;
pso.cfg.a.l_id_max=pso.cfg.p.l_id_max;
pso.cfg.a.v_id_max=pso.cfg.p.v_id_max;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           pso.p(article)          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.p.iter_max=10; % time_n_max determines the maximum number of iteration

% Initialize parameters of the PSO algorithm for a particle
% pso.p.best_p_id is necessary to keep track of the best particle.
% Without this index, relationship of H_o in the inner-loop recurrence will
% be messed up.
pso.p.best_p_id=0;
pso.p.P_BEST = zeros( pso.cfg.p.d,pso.cfg.p.size );
pso.p.G_BEST = zeros( pso.cfg.p.d,1 );
pso.p.P_fitness = zeros( 1,pso.cfg.p.size );
% Large enough numbers for a vector G_fitness
pso.p.G_fitness = pso.cfg.p.g_fitness.*ones( 1,pso.cfg.p.size );
pso.p.L_ID=rand( pso.cfg.p.d,pso.cfg.p.size );
pso.p.V_ID=rand( size(pso.p.L_ID) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         pso.a(ssociate)           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.a.iter_max=100.*pso.p.iter_max;
pso.a.P_fitness = zeros( 1,pso.cfg.a.size );
pso.a.g_fitness = pso.cfg.p.g_fitness;

for pp=1:pso.cfg.p.size,
    pso.a(pp).H_o=rand( csrn.cfg.N_h,pso.cfg.a.size );
    pso.a(pp).P_BEST = zeros( pso.cfg.a.d,pso.cfg.a.size );
    pso.a(pp).G_BEST = zeros( pso.cfg.a.d,1 );
    pso.a(pp).L_ID=rand( pso.cfg.a.d,pso.cfg.a.size );
    pso.a(pp).V_ID=rand( size(pso.a(pp).L_ID) );
end;
