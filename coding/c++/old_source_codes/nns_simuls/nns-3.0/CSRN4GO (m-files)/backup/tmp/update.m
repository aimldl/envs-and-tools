function [csrn,pso] = update(board,csrn,data,pso)

% update                A single update for the iteration
%
% All the input data sets X are inputed to the CSRN.
% The estimated CSRN outputs Y_HAT are compared to the target data sets
% Y_HAT.
% 

jj_max      = pso.p.iter_max;
fitness_t   = pso.cfg.p.target_fitness;
fitness_g   = pso.p.g_fitness;
size_p      = pso.cfg.p.size;
bb_max      = board.cfg.N_b;
board_max   = board.cfg.size;

jj=1;
while ( (jj<=jj_max) && (fitness_g>=fitness_t) ),
     for pp=1:size_p,
        csrn = interface_pso2csrn(csrn,pso,pp);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % NNs part
        e_t = 0;                                            % Total error
        for bb=1:bb_max,
            csrn = interface_data2csrn(csrn,data,bb,board_max);
            csrn = calculate_csrn_output(csrn,board_max);
            data.estimate(bb).SS = csrn.srn.Y_hat;
            e_t = update_total_error(data,bb,e_t);
        end;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        pso = update_pso_local_best(pso,e_t,jj,pp);
     end;
     pso = update_pso_global_best(board,csrn,pso,jj);
     fitness_g=pso.p.g_fitness;
     pso=update_pso_particle_locations(pso);
     jj = jj+1;
end;