function [csrn,pso]=psowhf_update_equations(board,csrn,params,pso,x,y,pp)
% pso_update_equations          Update equations in PSO
%                               PSO (Particle Swarm Optimization)
%     pp        particle_index
%
%     pso.cfg.w=0.8;
%     pso.cfg.c1=2;
%     pso.cfg.c2=2;
%     pso.cfg.target_fitness=10^-3;
%     pso.cfg.l_id_max=2.0;
%     pso.cfg.v_id_max=100;
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
%     params.ERROR_CURVE=zeros(params.epoch_max,board.max_board,board.max_board);

% Use temporary variable names 
%    because, e.g., pso.particle.L_ID is too lengthy.
L_ID=pso.particle.L_ID;
V_ID=pso.particle.V_ID;
P_BEST=pso.particle.P_BEST;
G_BEST=pso.particle.G_BEST;

w=pso.cfg.particle.w;
c1=pso.cfg.particle.c1;
c2=pso.cfg.particle.c2;

l_id_max=pso.cfg.particle.l_id_max;
v_id_max=pso.cfg.particle.v_id_max;
size_p=pso.cfg.particle.size;
dimension_p=pso.cfg.particle.d;

for pp=1:size_p,
    for dd=1:dimension_p,
        V_ID(dd,pp) = w.*V_ID(dd,pp)+ c1.*rand.*( P_BEST(dd,pp)-L_ID(dd,pp) )+ c2.*rand.*( G_BEST(dd,1)-L_ID(dd,pp) );
        if ( V_ID(dd,pp)>v_id_max ),
            V_ID(dd,pp)=v_id_max;
        elseif ( V_ID(dd,pp)<-v_id_max ),
            V_ID(dd,pp)=-v_id_max;
        end;
    end;    
end;

L_ID = L_ID + V_ID;

for pp=1:size_p,
    for dd=1:dimension_p,
        if ( L_ID(dd,pp)>l_id_max ),
            L_ID(dd,pp)=l_id_max;
        elseif ( L_ID(dd,pp)<-l_id_max ),
            L_ID(dd,pp)=-l_id_max;
        end;
    end;    
end;

% Store the updated location and velocity back to structure pso
pso.particle.L_ID=L_ID;
pso.particle.V_ID=V_ID;
