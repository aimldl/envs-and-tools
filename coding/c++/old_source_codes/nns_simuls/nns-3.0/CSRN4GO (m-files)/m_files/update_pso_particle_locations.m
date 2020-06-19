function pso=update_pso_particle_locations(pso,N_n_max);

% update_pso_particle_locations       Update PSO particles locations
%
% The locations of particles are updated by two equations: velocity and
% location updates.

w=pso.cfg.p.w;
c1=pso.cfg.p.c1;
c2=pso.cfg.p.c2;

l_id_max=pso.cfg.p.l_id_max;
v_id_max=pso.cfg.p.v_id_max;
size_p=pso.cfg.p.size;

for N_n=2:N_n_max,
    L_ID=pso.p.id(N_n-1).L_ID;
    V_ID=pso.p.id(N_n-1).V_ID;
    P_BEST=pso.p.id(N_n-1).P_BEST;
    G_BEST=pso.p.id(N_n-1).G_BEST;

    dimension_p=pso.cfg.p.id(N_n-1).d;

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
    pso.p.id(N_n-1).L_ID=L_ID;
    pso.p.id(N_n-1).V_ID=V_ID;
end;