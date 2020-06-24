function cnns=interface_pso2cnns3(cnns,pso,pp_indx);
% interface_pso2cnns3     Map a PSO particle's location to CNNS
%                        (Cellular Neural Networks System).
%
% pp_indx particle_index
%
% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)

for N_n=2:cnns.cell.N_n_max,
    N_u = cnns.cell.id(N_n-1).N_u;
    N_h = cnns.cell.id(N_n-1).N_h;
    N_v = cnns.cell.id(N_n-1).N_v;
    
    tmp_row=N_h;
    tmp_clmn=N_u+N_v;
    
    TMP=reshape( pso.p.id(N_n-1).L_ID(:,pp_indx), tmp_row, tmp_clmn);

    cnns.cell.id(N_n-1).W_u=TMP(:,1:N_u);
    cnns.cell.id(N_n-1).W_v=TMP(:,tmp_clmn);
end;

%     tmp_row=cnns.cfg.N_h;
%     tmp_clmn=cnns.cfg.N_u+cnns.cfg.N_v;
%     TMP=reshape( pso.p.L_ID(:,pp_indx), tmp_row, tmp_clmn);
% 
%     cnns.cell.W_u=TMP(:,1:cnns.cfg.N_u);
%     cnns.cell.W_v=TMP(:,tmp_clmn);
