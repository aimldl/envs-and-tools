function [csrn,pso]=eval_best_SRN_output(board,csrn,params,pp,pso,x,y);
% eval_best_SRN_output
% 
% Compute the SRN output with the best particle.
% In other words, use pso.particle.G_BEST to compute the SRN output.

% First map the best particle's location to SRN weights
% This part is similar to function interface_pso2srn

tmp_row=csrn.config.No_neurons(2);
tmp_clmn=csrn.config.No_neurons(1)+(csrn.config.No_neurons(2)+2)+1;
TMP=reshape( pso.particle.G_BEST, tmp_row, tmp_clmn);

W_u=TMP(:,1:csrn.config.No_neurons(1));
W_h=TMP(:,csrn.config.No_neurons(1)+1:tmp_clmn-1);
W_v=TMP(:,tmp_clmn)';

% Compute the SRN output from the best training result or the global best. 
% This part is similar to SRNwHF
ttl_no_input=csrn.srn(x,y).input_length;
U=csrn.srn(x,y).Input;
% y_target is an integer STRING_SIZE ranges from -string_size_max to string_size_max.
y_target=board.at(board.time_n).STRING_SIZE(x,y);

D=tansig( W_u*U );
tmp_D=[D';ones(size(D'))];
H_o=csrn.srn(x,y).H_output;

% Hidden layer
% New H_o and W_h c are applied at each iteration.
% Which H_o should be used is an open question.
% Here H_o at the previous time, i.e. t_n-1, is used.
H_i=[];
for ii=1:csrn.config.No_neurons(2),
    H_i=[H_i,H_o];
end;
H_i=[H_i;tmp_D];
H_o=diag( W_h*H_i );

% Output layer
% Activation function for the output layer is floor.
y_hat= floor( W_v*H_o );

% Error calculation
error_y= abs( y_target-y_hat );

csrn.srn(x,y).error_y.Time(t_n)=pso.cfg.particle.g_fitness;

% Store the values
csrn.srn(x,y).H_output=H_o;
csrn.srn(x,y).v_output=y_hat;
csrn.srn(x,y).error_y.Time=error_y;
csrn.srn(x,y).W_u=W_u;
csrn.srn(x,y).W_h=W_h;
% Check this out
csrn.srn(x,y).W_v=W_v';
