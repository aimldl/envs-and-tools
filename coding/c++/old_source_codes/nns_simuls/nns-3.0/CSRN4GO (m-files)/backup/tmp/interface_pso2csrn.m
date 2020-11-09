function csrn=interface_pso2csrn(csrn,pso,pp);
% interface_pso2srn     Map a PSO particle's location to Neural Nets weights
%
% pp particle_index
%         [row_W,clmn_W] = size( csrn.srn.W );
%         [row_V,clmn_V] = size( csrn.srn.V );
%         pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%         pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%
%
%   Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
%   csrn.config.No_neurons=[3,1];
%   csrn.srn.W=rand( csrn.config.No_neurons(1),csrn.srn.input2nn_lengh );
%   csrn.srn.V=rand( csrn.config.No_neurons(2),csrn.config.No_neurons(1) );

% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)

tmp_row=csrn.cfg.N_h;
tmp_clmn=csrn.cfg.N_u+csrn.cfg.N_v;
TMP=reshape( pso.p.L_ID(:,pp), tmp_row, tmp_clmn);

csrn.srn.W_u=TMP(:,1:csrn.cfg.N_u);
csrn.srn.W_v=TMP(:,tmp_clmn);