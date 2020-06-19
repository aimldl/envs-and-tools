function csrn = update_CSRN_wt_my_PSO(board,csrn,params,pso)
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

% Interface the variable names
max_board=board.max_board;
t_max=pso.particle.time_n_max;
fitness_t=pso.cfg.particle.target_fitness;
fitness_g=pso.cfg.particle.g_fitness;
size_p=pso.cfg.particle.size;
is_show=pso.cfg.is_display_err;
divisor=pso.cfg.display_frequency;

for x=1:max_board,
    for y=1:max_board,
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  For a single node  
         t_n=1;
         csrn=interface_go2srn(board,csrn,params,x,y);  % Get the input to a CSRN
%         while ( (t_n<=t_max) && (fitness_g>=fitness_t) ),
         while ( (t_n<=t_max) && (fitness_g>=fitness_t) ),             
             % Compute the SRN output for many particles or candidate solutions,
             % and select a particle with the best fitness
             for pp=1:size_p,
                 csrn=interface_PSO2SRNwHF(csrn,pso,pp);
                 [csrn,pso]=SRNwHF(board,csrn,params,pp,pso,x,y);
                 [csrn,pso]=psowhf_update_local_best(board,csrn,params,pso,x,y,pp,t_n);
             end;
             [csrn,pso]=psowhf_update_global_best(board,csrn,params,pso,x,y,pp);
             [csrn,pso]=psowhf_store_g_fitness(board,csrn,pso,x,y,t_n);
             [csrn,pso]=psowhf_update_equations(board,csrn,params,pso,x,y,pp);
             % Note the SRN output is already computed or evaluted during
             % the training.
             fitness_g=csrn.srn(x,y).error_y.Time(t_n);
             if ( is_show==1 && mod(t_n, divisor) == 0 ),             
                 disp_g_fitness=sprintf('\t\t(%d, %d)\tt_n=%d\tG_{fitness}=%f',x,y,t_n,fitness_g);
                 disp(disp_g_fitness);
             end;
            % Feed back the output as an input
            % Determine the output
            
            % The outer-loop recurrence part
            fb_input_index=csrn.srn(x,y).fb_input_location;
            csrn.srn(x,y).Input( fb_input_index )=csrn.srn(x,y).v_output;
             t_n = t_n+1;
          end;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
    end;
end;