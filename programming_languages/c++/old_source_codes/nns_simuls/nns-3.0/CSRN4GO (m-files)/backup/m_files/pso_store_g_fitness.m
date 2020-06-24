function pso=pso_store_g_fitness(pso,x,y)
%function [csrn,pso]=pso_store_g_fitness(board,csrn,params,pso,x,y,pp)
% Just to see the performance improvement
pso.node(x,y).mse.At(pso.time_n) = pso.particles(x,y).g_fitness;