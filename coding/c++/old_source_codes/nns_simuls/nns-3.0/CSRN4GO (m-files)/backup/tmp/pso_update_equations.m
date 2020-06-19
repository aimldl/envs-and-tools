function [csrn,pso]=pso_update_equations(board,csrn,params,pso,x,y,pp)
% pso_update_equations          Update equations in PSO
%                               PSO (Particle Swarm Optimization)
%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.config.l_id_max=2.0;
%     pso.config.v_id_max=100;
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
%
%     params.ERROR_CURVE=zeros(params.epoch_max,board.max_board,board.max_board);

% Use temporary variable names 
%    because, e.g., pso.node(x,y).L_ID is too lengthy.
L_ID=pso.node(x,y).L_ID;
V_ID=pso.node(x,y).V_ID;
w=pso.config.w;
c1=pso.config.c1;
c2=pso.config.c2;
P_BEST=pso.node(x,y).P_BEST;
G_BEST=pso.node(x,y).G_BEST;
l_id_max=pso.config.l_id_max;
v_id_max=pso.config.v_id_max;

for pp=1:pso.node(x,y).size,
    for dd=1:pso.node(x,y).dimension,
        V_ID(dd,pp) = w.*V_ID(dd,pp)+ c1.*rand.*( P_BEST(dd,pp)-L_ID(dd,pp) )+ c2.*rand.*( G_BEST(dd,1)-L_ID(dd,pp) );
        if ( V_ID(dd,pp)>v_id_max ),
            V_ID(dd,pp)=v_id_max;
        elseif ( V_ID(dd,pp)<-v_id_max ),
            V_ID(dd,pp)=-v_id_max;
        end;
    end;    
end;

L_ID = L_ID + V_ID;

for pp=1:pso.node(x,y).size,
    for dd=1:pso.node(x,y).dimension,
        if ( L_ID(dd,pp)>l_id_max ),
            L_ID(dd,pp)=l_id_max;
        elseif ( L_ID(dd,pp)<-l_id_max ),
            L_ID(dd,pp)=-l_id_max;
        end;
    end;    
end;

% Store the updated location and velocity back to structure pso
pso.node(x,y).L_ID=L_ID;
pso.node(x,y).V_ID=V_ID;
