function csrn = update_CSRN_wt_PSO_deep(board,csrn,params,pso)
% update_CSRN     Update CSRN in depth
%
% A single sweep or update of CSRN corresponds to an update of all the SRNs
% in the cellular structure. An update of a SRN means a multiple number of
% updates within the SRN. In other words, the output of the FFNN in the SRN
% fed back to the input to the FFNN is updated a multiple number of times.
%
% The following double loop covers the cellular structure of this CSRN
% In other words, a single node corresponds to a single SRN in the loop, and
% visiting all the nodes through the loop (x and y) is a single sweep of a
% CSRN update.

for x=1:board.max_board,
    for y=1:board.max_board,
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
         pso.time_n=1;
         csrn=interface_go2srn(board,csrn,params,x,y);
         while ( (pso.time_n<=pso.time_n_max) && (pso.particles(x,y).g_fitness>=pso.config.target_fitness) ),
             % Compute the SRN output for many particles or candidate solutions,
             % and select a particle with the best fitness
             for pp=1:pso.particles(x,y).size,
                 csrn=interface_pso2srn(csrn,pso,x,y,pp);
                 csrn=SRN2(board,csrn,params,x,y);
                 [csrn,pso]=pso_update_local_best(board,csrn,params,pso,x,y,pp);
             end;
             [csrn,pso]=pso_update_global_best(board,csrn,params,pso,x,y,pp);
             pso=pso_store_g_fitness(pso,x,y);
             [csrn,pso]=pso_update_equations(board,csrn,params,pso,x,y,pp);
             disp(pso.particles(x,y).g_fitness);
             if ( pso.config.is_display_mse==1 && mod(pso.time_n, pso.config.display_frequency) == 0 ),             
                 disp_g_fitness=sprintf('\t\t(%d, %d)\tpso.time_n=%d\tG_{fitness}=%f',x,y,pso.time_n,pso.particles(x,y).g_fitness);
                 disp(disp_g_fitness);
             end;
             pso.time_n = pso.time_n+1;
          end;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
    end;
end;