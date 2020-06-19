function pso = update_pso_global_best3(pso,N_n_max);

% update_pso_global_best    Update the global best for PSO
%                           G_BEST is the global best.
for N_n=2:N_n_max,
    if ( pso.p.id(N_n-1).g_fitness > min(pso.p.id(N_n-1).P_fitness) ),
        [ pso.p.id(N_n-1).g_fitness,best_p ]= min(pso.p.id(N_n-1).P_fitness);
        pso.p.id(N_n-1).G_BEST=pso.p.id(N_n-1).P_BEST(:,best_p);
        pso.p.id(N_n-1).best_p=best_p;
    end;
end;