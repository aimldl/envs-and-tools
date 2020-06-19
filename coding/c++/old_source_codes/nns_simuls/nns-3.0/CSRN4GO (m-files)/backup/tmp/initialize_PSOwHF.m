function pso=initialize_PSOwHF(board,csrn),
% initialize_pso        Initialize PSO (Particle Swarm Intelligence)
%
%    Usage: this function should be called after initializing board and
%    csrn.
%           board=initialize_board();
%           csrn=initialize_csrn(board);
%           pso=initialize_pso(board,csrn);
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

% Level of scope
%   node        A node corresponds to a SNR and multiple particles are
%               employed to find the best solution for the node
%   particle    A particle leads many associates that help the particle
%               find the solution
%   associate   A associate 
% On all three levels, the goal is shared. In other words, the target
% fitness is identical.

% Associate
% http://dictionary.reference.com/browse/associate
% 1. to connect or bring into relation, as thought, feeling,memory, etc.
% 2. to join as a companion, partner, or ally 
% 3. to unite; combine 
% 7. a person who shares actively in anything as a business, enterprise, or
% undertaking; partner; colleague 
% 8. a companion or comrade 

% Hierarchy of the variables
% pso
%       .cfg    (Configuration)
%           .particle
%               .associate
%       .particle
%           .associate

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           pso.cfg              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.cfg.is_display_err=0;
pso.cfg.display_frequency=10;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       pso.cfg.particle         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% There is only one particle for 2x2 using symmetry.
x=1;y=1;
[row_W_u,clmn_W_u] = size( csrn.srn(x,y).W_u );
[row_W_h,clmn_W_h] = size( csrn.srn(x,y).W_h );
[row_W_v,clmn_W_v] = size( csrn.srn(x,y).W_v );

pso.cfg.particle.d=row_W_u.*clmn_W_u+row_W_h.*clmn_W_h+row_W_v.*clmn_W_v;   % dimension
pso.cfg.particle.size=20;                   % Number of particles        
pso.cfg.particle.w=0.8;
pso.cfg.particle.c1=2;
pso.cfg.particle.c2=2;
pso.cfg.particle.l_id_max=2.0;
pso.cfg.particle.v_id_max=100;
pso.cfg.particle.target_fitness=0;           % Number of acceptable errors
% Global fitness
% An arbitrary number large enough to update the global best at the
% beginning of the iteration. The following condition is in mind.
% if ( pso.cfg.particle.g_fitness > min(pso.particle.P_fitness) )
pso.cfg.particle.g_fitness = 10^13;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   pso.cfg.particle.associate   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.cfg.associate.d=row_W_h.*clmn_W_h;      % dimension
pso.cfg.associate.size=10;                 % Number of associates per particle
pso.cfg.associate.w=0.2;
pso.cfg.associate.c1=1;
pso.cfg.associate.c2=1;
pso.cfg.associate.target_fitness=pso.cfg.particle.target_fitness;
pso.cfg.associate.g_fitness=pso.cfg.particle.g_fitness;
pso.cfg.associate.l_id_max=pso.cfg.particle.l_id_max;
pso.cfg.associate.v_id_max=pso.cfg.particle.v_id_max;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   pso.particle                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.particle.time_n_max=10; % time_n_max determines the maximum number of iteration

% Initialize parameters of the PSO algorithm for a particle
% pso.particle.best_p_id is necessary to keep track of the best particle.
% Without this index, relationship of H_o in the inner-loop recurrence will
% be messed up.
pso.particle.best_p_id=0;
pso.particle.P_BEST = zeros( pso.cfg.particle.d,pso.cfg.particle.size );
pso.particle.G_BEST = zeros( pso.cfg.particle.d,1 );
pso.particle.P_fitness = zeros( 1,pso.cfg.particle.size );
% Large enough numbers for a vector G_fitness
pso.particle.G_fitness = pso.cfg.particle.g_fitness.*ones( 1,pso.cfg.particle.size );
pso.particle.L_ID=rand( pso.cfg.particle.d,pso.cfg.particle.size );
pso.particle.V_ID=rand( size(pso.particle.L_ID) );
%pso.particle.mse.At=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   pso.particle.particle.associate   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.associate.time_m_max=100.*pso.particle.time_n_max;

pso.associate.P_fitness = zeros( 1,pso.cfg.associate.size );
pso.associate.g_fitness = pso.cfg.particle.g_fitness;

for pp=1:pso.cfg.particle.size,
    pso.a(pp).H_o=rand( csrn.cfg.No_neurons(2),pso.cfg.associate.size );
    pso.a(pp).P_BEST = zeros( pso.cfg.associate.d,pso.cfg.associate.size );
    pso.a(pp).G_BEST = zeros( pso.cfg.associate.d,1 );
%   This needs to be emptied at every time    
%    pso.a(pp).P_fitness = zeros( 1,pso.cfg.associate.size );
    pso.a(pp).L_ID=rand( pso.cfg.associate.d,pso.cfg.associate.size );
    pso.a(pp).V_ID=rand( size(pso.a(pp).L_ID) );
end;
