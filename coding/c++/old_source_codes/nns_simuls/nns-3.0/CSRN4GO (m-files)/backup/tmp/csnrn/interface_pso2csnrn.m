function cnns=interface_pso2csnrn(cnns,pso,pp_indx);
% interface_pso2csnrn     Map a PSO particle's location to CSNRN
%                        (Cellular Simultaneous Nested Recurrence Network).
%
% pp_indx particle_index
%
% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)
%
% See also interface_pso2cnns

tmp_row=cnns.cfg.N_h;
% This part is different from interface_pso2cnns
tmp_clmn=cnns.cfg.N_u+(cnns.cfg.N_h+2)+cnns.cfg.N_v;
% This part is different from interface_pso2cnns
TMP=reshape( pso.p.L_ID(:,pp_indx), tmp_row, tmp_clmn);

cnns.cell.W_u=TMP(:,1:cnns.cfg.N_u);
% This part is different from interface_pso2cnns
cnns.cell.W_h=TMP(:,cnns.cfg.N_u+1:tmp_clmn-1);
% This part is different from interface_pso2cnns
cnns.cell.W_v=TMP(:,tmp_clmn);
