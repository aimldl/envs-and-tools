function csrn=interface_pso2srn(csrn,pso,pp,varargin);
%function csrn=interface_pso2srn(csrn,pso,x,y,pp);
% interface_pso2srn     Map a PSO particle's location to Neural Nets weights
%
% pp particle_index
%         [row_W,clmn_W] = size( csrn.srn(x,y).W );
%         [row_V,clmn_V] = size( csrn.srn(x,y).V );
%         pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%         pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%
%         csrn.config.No_neurons=[ N_u, N_h, N_v ];
%         csrn.srn(x,y).W_u=zeros( N_h,N_u );
%         csrn.srn(x,y).W_h=zeros( N_h,N_e  );
%         csrn.srn(x,y).W_v=zeros( 1,N_h );
% When X(:,1) is a 75x1 row vector
% reshape(X(:,1),3,8)
tmp_row=csrn.cfg.No_neurons(2);
tmp_clmn=csrn.cfg.No_neurons(1)+(csrn.cfg.No_neurons(2)+2)+1;
TMP=reshape( pso.particle.L_ID(:,pp), tmp_row, tmp_clmn);

if ( nargin==3 ),
    % To use symmetry for a 2x2 board, use just a single node.
    x=1;y=1;
elseif ( nargin==5 ),
    x=varargin{1};
    y=varargin{2};
end;

csrn.srn(x,y).W_u=TMP(:,1:csrn.cfg.No_neurons(1));
csrn.srn(x,y).W_h=TMP(:,csrn.cfg.No_neurons(1)+1:tmp_clmn-1);
csrn.srn(x,y).W_v=TMP(:,tmp_clmn);