function pso = update_pso_local_best3(pso,e_t,nn_indx,N_n_max,pp_indx);

% update_pso_local_best3
%
% Update PSO local bests for ALL the neural networks.
% Here there are three different types of neurons.
% local_best is P_BEST
% e_t     total error

for N_n=2:N_n_max,
    if ( (pso.p.id(N_n-1).P_fitness(1,pp_indx)==0) && (nn_indx==1) ),
        pso.p.id(N_n-1).P_fitness(1,pp_indx)       = e_t(N_n-1);
        pso.p.id(N_n-1).P_BEST(:,pp_indx)          = pso.p.id(N_n-1).L_ID(:,pp_indx);
    else,
       if ( pso.p.id(N_n-1).P_fitness(1,pp_indx)>e_t(N_n-1) ),
           pso.p.id(N_n-1).P_fitness(1,pp_indx)    = e_t(N_n-1);
           pso.p.id(N_n-1).P_BEST(:,pp_indx)       = pso.p.id(N_n-1).L_ID(:,pp_indx);       
       end;
    end;
end;