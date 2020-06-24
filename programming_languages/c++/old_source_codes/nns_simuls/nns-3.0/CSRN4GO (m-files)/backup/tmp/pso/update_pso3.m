function [data,nns,pso] = update_pso3(board,nns,data,pso,nn,nnc_type)

% update_pso        A single update of PSO (Particle Swarm Optimization)
%
% All the input data sets X are inputed to the NNS (Neural Networks System).
% The estimated NNS outputs Y_HAT are compared to the target data sets
% Y_HAT.

size_p      = pso.cfg.p.size;
bb_max      = board.cfg.N_b;
board_max   = board.cfg.size;
N_n_max     = nns.cell.N_n_max;
if ( nnc_type=='mlp' ),
     for pp=1:size_p,
        nns = interface_pso2cnns3(nns,pso,pp);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % NNs part
        e_t = zeros(1,N_n_max-1);                             % Total error
        for bb=1:bb_max,
            nns = interface_data2cnns3(nns,data,bb,board_max);
            [nns,data,e_t] = calculate_cmlp_output3(nns,data,e_t,bb,board_max);
        end;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        pso = update_pso_local_best3(pso,e_t,nn,N_n_max,pp);
     end;
     pso = update_pso_global_best3(pso,N_n_max);
     pso = add_fitness_g3(pso,N_n_max);             % Merge the total error
     pso=update_pso_particle_locations3(pso,N_n_max);
elseif( nnc_type=='srn' ),
     oo_max=nns.cfg.iter_max;
     for pp=1:size_p,
        nns = interface_pso2cnns3(nns,pso,pp);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % NNs part
        e_t = zeros(1,N_n_max-1);                             % Total error
        for bb=1:bb_max,
            nns = interface_data2cnns3(nns,data,bb,board_max);
            [nns,data,e_t] = calculate_csrn_output3(nns,data,e_t,bb,board_max,oo_max);
        end;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        pso = update_pso_local_best3(pso,e_t,nn,N_n_max,pp);
     end;
     pso = update_pso_global_best3(pso,N_n_max);
     pso = add_fitness_g3(pso,N_n_max);             % Merge the total error
     pso=update_pso_particle_locations3(pso,N_n_max);
elseif( nnc_type=='snr' ),
     % The difference of SNRNs is the existence of the hidden layer
     % weights. More weights mean a larger domain in PSO.
     %
     oo_max=nns.cfg.iter_max;
     size_a=pso.cfg.a.size;
     for pp=1:size_p,
        nns = interface_pso2csnrn(nns,pso,pp);
        pso=init_a_pso(pso);
        for aa=1:size_a,
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            % NNs part
            e_t = 0;                                            % Total error
            H_o=pso.a(pp).H_o;
            for bb=1:bb_max,
                nns = interface_data2cnns(nns,data,bb,board_max);
                nns = calculate_csnrn_output(nns,board_max,oo_max);
                data.estimate(bb).SS = nns.cell.Y_hat;
                e_t = update_total_error(data,bb,e_t);
            end;
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        end;
        pso = update_pso_local_best(pso,e_t,nn,pp);
     end;
     pso = update_pso_global_best(pso);
     pso=update_pso_particle_locations(pso);
end;