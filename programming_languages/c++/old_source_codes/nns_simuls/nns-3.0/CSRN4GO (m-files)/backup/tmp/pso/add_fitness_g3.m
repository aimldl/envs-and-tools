function pso=add_fitness_g3(pso,N_n_max);

% update_fitness_g3
%
% This function adds individual global fitness values.

total_error=0;
for N_n=2:N_n_max,
    total_error=total_error+pso.p.id(N_n-1).g_fitness;
end;
pso.p.g_fitness=total_error;
