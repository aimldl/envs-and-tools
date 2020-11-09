function csrn=ffnn(board,csrn,params,x,y)
% ffnn      Feed-Forward Neural Networks in the sequential mode
%
% A function for MLP (Multi-Layer Perceptron)
% I have to use sequential mode training, not batch mode training because 
% stones in Go are presented sequentially.
%

% Variable mapping.
%U=csrn.srn(x,y).Input2nn;
%ttl_no_input=csrn.srn(x,y).input2nn_lengh;
ttl_no_input=csrn.srn(x,y).input_lengh;
U=csrn.srn(x,y).Input;
W=csrn.srn(x,y).W;
V=csrn.srn(x,y).V;

% Compute the NN output
% Note that input to a NN should be [-1,1];
% Therefore, tansig should be used because tansig(x) in [-1,1].
% logsig(x) is between [0,1]
D=tansig(W*U);    
y_hat=V'*D;

% Error calculation
if ( params.opt_input==1 ),
    y_target=board.EVAL_FN(x,y);
elseif ( params.opt_input==2 ),
    % Normalize STRING_SIZE by string_size_max.
    % Then y_target ranges from -1 to 1 because 
    % STRING_SIZE ranges from -string_size_max to string_size_max.
    y_target=board.at(board.time_n).STRING_SIZE(x,y)/board.string_size_max;
elseif ( params.opt_input==3 ),
    y_target=board.at(board.time_n).STRING_SIZE(x,y)/board.string_size_max;
end;
error_y=y_target-y_hat;
mse=sum(error_y.^2)./ttl_no_input;

% Store the values
csrn.srn(x,y).output.At(csrn.time_n)=y_hat;
csrn.srn(x,y).error_y.At(csrn.time_n)=error_y;
csrn.srn(x,y).mse_tmp.At(csrn.time_n)=mse;
%(board.time_n)