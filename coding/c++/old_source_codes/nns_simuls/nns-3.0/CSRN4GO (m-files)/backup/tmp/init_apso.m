function pso=init_apso(board,nns,nn_type),
% init_pso              Initialize PSO (Particle Swarm Intelligence)
%
% Velocity update equation 
% The velocity update equation (1) is comprised of:
%    inertia of the previous velocity, 
%    the cognitive acceleration term, and 
%    the social acceleration term. 
% This velocity is moving towards both to the local best of the given particle and the global best positions of the whole population. 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         pso.cfg.p(article)        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if ( nn_type=='mlp' ),
    % There is only one particle for 2x2 using symmetry.
    [row_W_u,clmn_W_u] = size( nns.cell.W_u );
    [row_W_v,clmn_W_v] = size( nns.cell.W_v );
elseif ( nn_type=='srn' ),
    disp('To be continued...');
end;
pso.cfg.p.d=row_W_u.*clmn_W_u+row_W_v.*clmn_W_v;   % dimension
pso.cfg.p.size=20;                   % Number of particles        
pso.cfg.p.w=0.8;
pso.cfg.p.c1=2;
pso.cfg.p.c2=2;
pso.cfg.p.l_id_max=2.0;
pso.cfg.p.v_id_max=100;
pso.cfg.p.target_fitness=0;           % Number of acceptable errors

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           pso.p(article)          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.p.iter_max=10; % time_n_max determines the maximum number of iteration

% Initialize parameters of the PSO algorithm for a particle
% pso.p.best_p_id is necessary to keep track of the best particle.
% Without this index, relationship of H_o in the inner-loop recurrence will
% be messed up.
pso.p.best_p=0;
% Global fitness
% An arbitrary number large enough to update the global best at the
% beginning of the iteration. The following condition is in mind.
% if ( pso.cfg.p.g_fitness > min(pso.p.P_fitness) )
pso.p.g_fitness = 10^13;
pso.p.P_BEST = zeros( pso.cfg.p.d,pso.cfg.p.size );
pso.p.G_BEST = zeros( pso.cfg.p.d,1 );
pso.p.P_fitness = zeros( 1,pso.cfg.p.size );
% Large enough numbers for a vector G_fitness
pso.p.G_fitness = pso.p.g_fitness.*ones( 1,pso.cfg.p.size );
pso.p.L_ID=rand( pso.cfg.p.d,pso.cfg.p.size );
pso.p.V_ID=rand( size(pso.p.L_ID) );