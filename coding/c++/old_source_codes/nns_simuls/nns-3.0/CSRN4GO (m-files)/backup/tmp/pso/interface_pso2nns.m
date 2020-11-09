function nns=interface_pso2nns(nns,pso,pp);
% interface_pso2nns     Map a PSO particle's location to Neural Nets weights
%
% pp particle_index
%
% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)

tmp_row=nns.cfg.N_h;
tmp_clmn=nns.cfg.N_u+nns.cfg.N_v;
TMP=reshape( pso.p.L_ID(:,pp), tmp_row, tmp_clmn);

nns.srn.W_u=TMP(:,1:nns.cfg.N_u);
nns.srn.W_v=TMP(:,tmp_clmn);