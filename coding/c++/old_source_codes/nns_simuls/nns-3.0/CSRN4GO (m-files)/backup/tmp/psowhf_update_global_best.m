function [csrn,pso]=psowhf_update_global_best(board,csrn,params,pso,x,y,pp)

%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.particle.size=5;                  % Number of particles        
%     [row_W,clmn_W] = size( csrn.srn(x,y).W );
%     [row_V,clmn_V] = size( csrn.srn(x,y).V );
%     pso.particle.dimension=row_W.*clmn_W+row_V.*clmn_V;
%     % Initialize parameters of the PSO algorithm for a node at (x,y)
%     % Note these matrice will be expanded as "pso.particle.size"
%     % is expanded.
%     pso.particle.P_BEST = zeros( pso.particle.dimension,pso.particle.size );
%     pso.particle.G_BEST = zeros( pso.particle.dimension,1 );
%     pso.particle.P_fitness = zeros( 1,pso.particle.size );
%     pso.particle.g_fitness = 10^6;
%     pso.particle.L_ID=rand( pso.particle.dimension,pso.particle.size );
%     pso.particle.V_ID=rand( size(pso.particle.L_ID) );
%
%      params.ERROR_CURVE=zeros(params.epoch_max,board.max_board,board.max_board);


% Update the global best, i.e. pso.particle.G_BEST
if ( pso.cfg.particle.g_fitness > min(pso.particle.P_fitness) ),
    [ pso.cfg.particle.g_fitness,best_particle ]= min(pso.particle.P_fitness);
    pso.particle.G_BEST=pso.particle.P_BEST(:,best_particle);
    % This is absolutely necessary. 
    % Without this index, the hidden layer recurrence will be messed up. 
    pso.particle.best_p_id=best_particle;
end;
%    csrn.srn(x,y).error_y.Time(t_n)=pso.cfg.particle.g_fitness;
%pso.particle.mse.At(pso.time_n) = pso.particle.g_fitness;
