function pso=init_pso(pso,N_n_max),
% init_pso              Initialize PSO (Particle Swarm Intelligence)
%
% Velocity update equation 
% The velocity update equation (1) is comprised of:
%    inertia of the previous velocity, 
%    the cognitive acceleration term, and 
%    the social acceleration term. 
% This velocity is moving towards both to the local best of the given particle and the global best positions of the whole population. 
%
% See also init_apso

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           pso.p(article)          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialize parameters of the PSO algorithm for a particle
% pso.p.best_p_id is necessary to keep track of the best particle.
% Without this index, relationship of H_o in the inner-loop recurrence will
% be messed up.

pso.p.g_fitness = 10^200;

for N_n=2:N_n_max,
    pso.p.id(N_n-1).best_p=0;
    % Global fitness
    % An arbitrary number large enough to update the global best at the
    % beginning of the iteration. The following condition is in mind.
    % if ( pso.cfg.p.g_fitness > min(pso.p.P_fitness) )
    pso.p.id(N_n-1).P_BEST = zeros( pso.cfg.p.id(N_n-1).d,pso.cfg.p.size );
    pso.p.id(N_n-1).G_BEST = zeros( pso.cfg.p.id(N_n-1).d,1 );
    pso.p.id(N_n-1).P_fitness = zeros( 1,pso.cfg.p.size );
    pso.p.id(N_n-1).g_fitness = 10^13;
    % Large enough numbers for a vector G_fitness
    pso.p.id(N_n-1).G_fitness = pso.p.id(N_n-1).g_fitness.*ones( 1,pso.cfg.p.size );
    pso.p.id(N_n-1).L_ID=rand( pso.cfg.p.id(N_n-1).d,pso.cfg.p.size );
    pso.p.id(N_n-1).V_ID=rand( size(pso.p.id(N_n-1).L_ID) );
    % Associates are initialized in a separate m-file.
end;