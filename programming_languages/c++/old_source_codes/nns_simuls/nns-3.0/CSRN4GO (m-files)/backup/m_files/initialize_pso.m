function pso=initialize_pso(board,csrn),
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

pso.config.is_display_mse=0;
pso.config.display_frequency=10;
pso.config.w=0.8;
pso.config.c1=2;
pso.config.c2=2;
pso.config.target_fitness=10^-3;
pso.config.l_id_max=2.0;
pso.config.v_id_max=100;

% Epoch, time n, or iteration counter for PSO
pso.time_n=1;
% time_n_max determines the maximum number of iteration
pso.time_n_max=10;

for x=1:board.max_board,
    for y=1:board.max_board,
        pso.particles(x,y).size=5;                  % Number of particles        
        [row_W,clmn_W] = size( csrn.srn(x,y).W );
        [row_V,clmn_V] = size( csrn.srn(x,y).V );
        pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
        % Initialize parameters of the PSO algorithm for a node at (x,y)
        % Note these matrice will be expanded as "pso.particles(x,y).size"
        % is expanded.
        pso.particles(x,y).P_BEST = zeros( pso.particles(x,y).dimension,pso.particles(x,y).size );
        pso.particles(x,y).G_BEST = zeros( pso.particles(x,y).dimension,1 );
        pso.particles(x,y).P_fitness = zeros( 1,pso.particles(x,y).size );
        % An arbitrary number large enough to update the global best at the
        % beginning of the iteration. The following condition is in mind.
        % if ( pso.particles(x,y).g_fitness > min(pso.particles(x,y).P_fitness) )
        pso.particles(x,y).g_fitness = 10^6;        
        pso.particles(x,y).mse.At=0;
        pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
        pso.particles(x,y).V_ID=rand( size(pso.particles(x,y).L_ID) );
    end;
end;


