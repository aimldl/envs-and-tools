function csrn=interface_pso2srn(csrn,pso,x,y,pp);
% interface_pso2srn     Map a PSO particle's location to Neural Nets weights
%
% pp particle_index
%         [row_W,clmn_W] = size( csrn.srn(x,y).W );
%         [row_V,clmn_V] = size( csrn.srn(x,y).V );
%         pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%         pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%
%
%   Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
%   csrn.config.No_neurons=[3,1];
%   csrn.srn(x,y).W=rand( csrn.config.No_neurons(1),csrn.srn(x,y).input2nn_lengh );
%   csrn.srn(x,y).V=rand( csrn.config.No_neurons(2),csrn.config.No_neurons(1) );

% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)
TMP=reshape( pso.particles(x,y).L_ID(:,pp), csrn.config.No_neurons(1), csrn.srn(x,y).input_lengh+csrn.config.No_neurons(2));
csrn.srn(x,y).W=TMP(:,1:csrn.srn(x,y).input_lengh);
csrn.srn(x,y).V=TMP(:,csrn.srn(x,y).input_lengh+1:csrn.srn(x,y).input_lengh+csrn.config.No_neurons(2));

