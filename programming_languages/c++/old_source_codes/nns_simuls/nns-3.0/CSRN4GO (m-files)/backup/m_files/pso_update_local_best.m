function [csrn,pso]=pso_update_local_best(board,csrn,params,pso,x,y,pp)

%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.node(x,y).size=5;                  % Number of particles        
%     [row_W,clmn_W] = size( csrn.srn(x,y).W );
%     [row_V,clmn_V] = size( csrn.srn(x,y).V );
%     pso.node(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%     % Initialize parameters of the PSO algorithm for a node at (x,y)
%     % Note these matrice will be expanded as "pso.node(x,y).size"
%     % is expanded.
%     pso.node(x,y).P_BEST = zeros( pso.node(x,y).dimension,pso.node(x,y).size );
%     pso.node(x,y).G_BEST = zeros( pso.node(x,y).dimension,1 );
%     pso.node(x,y).P_fitness = zeros( 1,pso.node(x,y).size );
%     pso.node(x,y).g_fitness = 10^6;
%     pso.node(x,y).L_ID=rand( pso.node(x,y).dimension,pso.node(x,y).size );
%     pso.node(x,y).V_ID=rand( size(pso.node(x,y).L_ID) );

% Update the local best or particel best, i.e. pso.node(x,y).P_BEST

if ( (pso.node(x,y).P_fitness(1,pp)==0) && (pso.time_n==1) ),
    pso.node(x,y).P_fitness(1,pp)=csrn.srn(x,y).mse_tmp.At(csrn.time_n);
    pso.node(x,y).P_BEST(:,pp)=pso.node(x,y).L_ID(:,pp);
else,
   if ( pso.node(x,y).P_fitness(1,pp)>csrn.srn(x,y).mse.At(csrn.time_n) ),
       pso.node(x,y).P_fitness(1,pp)=csrn.srn(x,y).mse_tmp.At(csrn.time_n);
       pso.node(x,y).P_BEST(:,pp)=pso.node(x,y).L_ID(:,pp);       
   end;
end;