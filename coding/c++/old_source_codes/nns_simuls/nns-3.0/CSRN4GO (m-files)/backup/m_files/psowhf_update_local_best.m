function [csrn,pso]=psowhf_update_local_best(board,csrn,params,pso,x,y,pp,t_n)

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

% This part is slightly different from the origninal PSO.
% The global best for associates compete with the particle level's local
% best.

if ( (pso.particle.P_fitness(1,pp)==0) && (t_n==1) ),
    pso.particle.P_fitness(1,pp)=pso.associate.g_fitness;
    % Now, merge associates level into the particle level.
    % i.e. the best associate's location is merged into a particle's local
    % best location.
    w_u_end=csrn.srn(x,y).w_u_end;
    w_h_end=csrn.srn(x,y).w_h_end;    
    pso.particle.L_ID(w_u_end+1:w_h_end,pp)=pso.a(pp).G_BEST;
    pso.particle.P_BEST(:,pp)=pso.particle.L_ID(:,pp);
else,
   if ( pso.particle.P_fitness(1,pp)>pso.associate.g_fitness ),
       pso.particle.P_fitness(1,pp)=pso.associate.g_fitness;
       w_u_end=csrn.srn(x,y).w_u_end;
       w_h_end=csrn.srn(x,y).w_h_end;    
       pso.particle.L_ID(w_u_end+1:w_h_end,pp)=pso.a(pp).G_BEST;
       pso.particle.P_BEST(:,pp)=pso.particle.L_ID(:,pp);
   end;
end;