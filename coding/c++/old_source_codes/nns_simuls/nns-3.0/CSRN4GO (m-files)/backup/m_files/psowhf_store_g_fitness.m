function [csrn,pso]=psowhf_store_g_fitness(board,csrn,pso,x,y,t_n)
%function [csrn,pso]=pso_store_g_fitness(board,csrn,params,pso,x,y,pp)
% Just to see the performance improvement
csrn.srn(x,y).error_y.Time(t_n)=pso.cfg.particle.g_fitness;
% g_fitness = error_y=y_hat-y_target
% so, y_hat=g_fitness + y_target
y_target=board.at(board.time_n).STRING_SIZE(x,y);
csrn.srn(x,y).v_output=pso.cfg.particle.g_fitness+y_target;

