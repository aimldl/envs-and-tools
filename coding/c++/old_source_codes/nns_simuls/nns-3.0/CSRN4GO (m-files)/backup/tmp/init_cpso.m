function cpso=init_cpso(board,csrn),
% init_cpso        Initialize CPSO (Cellular Particle Swarm Intelligence)
%
% One CPSO particle corresponds to a set of the legacy PSO particles.
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
%         cpso.cfg.p(article)       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% There is only one particle for 2x2 using symmetry.
[row_W_u,clmn_W_u] = size( csrn.srn.W_u );
[row_W_h,clmn_W_h] = size( csrn.srn.W_h );
[row_W_v,clmn_W_v] = size( csrn.srn.W_v );

cpso.cfg.p.d=row_W_u.*clmn_W_u+row_W_h.*clmn_W_h+row_W_v.*clmn_W_v;   % dimension
cpso.cfg.p.size=20;                   % Number of particles        
cpso.cfg.p.w=0.8;
cpso.cfg.p.c1=2;
cpso.cfg.p.c2=2;
cpso.cfg.p.l_id_max=2.0;
cpso.cfg.p.v_id_max=100;
cpso.cfg.p.target_fitness=0;           % Number of acceptable errors
% Global fitness
% An arbitrary number large enough to update the global best at the
% beginning of the iteration. The following condition is in mind.
% if ( cpso.cfg.p.g_fitness > min(cpso.p.P_fitness) )
cpso.cfg.p.g_fitness = 10^13;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      cpso.cfg.p.a(ssociate)        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cpso.cfg.a.d=row_W_h.*clmn_W_h;      % dimension
cpso.cfg.a.size=10;                 % Number of associates per particle
cpso.cfg.a.w=0.2;
cpso.cfg.a.c1=1;
cpso.cfg.a.c2=1;
cpso.cfg.a.target_fitness=cpso.cfg.p.target_fitness;
cpso.cfg.a.g_fitness=cpso.cfg.p.g_fitness;
cpso.cfg.a.l_id_max=cpso.cfg.p.l_id_max;
cpso.cfg.a.v_id_max=cpso.cfg.p.v_id_max;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           cpso.p(article)          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cpso.p.iter_max=10; % time_n_max determines the maximum number of iteration

% Initialize parameters of the PSO algorithm for a particle
% cpso.p.best_p_id is necessary to keep track of the best particle.
% Without this index, relationship of H_o in the inner-loop recurrence will
% be messed up.
cpso.p.best_p_id=0;
cpso.p.P_BEST = zeros( cpso.cfg.p.d,cpso.cfg.p.size );
cpso.p.G_BEST = zeros( cpso.cfg.p.d,1 );
cpso.p.P_fitness = zeros( 1,cpso.cfg.p.size );
% Large enough numbers for a vector G_fitness
cpso.p.G_fitness = cpso.cfg.p.g_fitness.*ones( 1,cpso.cfg.p.size );
%cpso.p.L_ID=rand( cpso.cfg.p.d,cpso.cfg.p.size );
cpso.p.L_ID=rand( cpso.cfg.p.d,board.cfg.N_s );
cpso.p.V_ID=rand( size(cpso.p.L_ID) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         cpso.a(ssociate)           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cpso.a.iter_max  = 100.*cpso.p.iter_max;
cpso.a.P_fitness = zeros( 1,cpso.cfg.a.size );
cpso.a.g_fitness = cpso.cfg.p.g_fitness;

for pp=1:cpso.cfg.p.size,
    cpso.a(pp).H_o=rand( csrn.cfg.N_h,cpso.cfg.a.size );
    cpso.a(pp).P_BEST = zeros( cpso.cfg.a.d,cpso.cfg.a.size );
    cpso.a(pp).G_BEST = zeros( cpso.cfg.a.d,1 );
    %cpso.a(pp).L_ID=rand( cpso.cfg.a.d,cpso.cfg.a.size );
    cpso.a(pp).L_ID=rand( cpso.cfg.a.d,board.cfg.N_s );
    cpso.a(pp).V_ID=rand( size(cpso.a(pp).L_ID) );
end;
