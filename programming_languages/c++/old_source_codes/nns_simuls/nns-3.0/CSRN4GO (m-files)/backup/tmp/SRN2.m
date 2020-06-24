function csrn=SRN2(board,csrn,params,x,y)
% SRN       A module for Simultaneous Recurrent Network
%
% How the SRN structure is constrcuted.
%
%    This SRN module contains a FFNN (Feed-forward Neural Networks).
%    The FFNN's output is fed back as input to the FFNN, and this constructs a
%    Recurrent Network structure.
%    This feedback is iterated a multiple number of times, which constitutes a
%    Simultaneous Recurrent Network structure.
%
% The training algorithm is incorporated into this module.
%    The reason is because the weights of the FFNN should be updated as the
%    FFNN output is iteratively fedback to its input.

% Note that input to a NN should be [-1,1];

% Variable mapping.
%U=csrn.srn(x,y).Input2nn;
%ttl_no_input=csrn.srn(x,y).input2nn_lengh;
ttl_no_input=csrn.srn(x,y).input_lengh;
U=csrn.srn(x,y).Input;
W=csrn.srn(x,y).W;
H=csrn.srn(x,y).H_neuron_out.At(csrn.time_n,:);
V=csrn.srn(x,y).V;

% Compute the NN output
% Note that input to a NN should be [-1,1];
% Therefore, tansig should be used because tansig(x) in [-1,1].
% logsig(x) is between [0,1]
D=tansig( W*U );
% The recurrency in the hidden layer:
% All the hidden layer outputs are summed and input to the node.

% Do I need to iterate in the hidden layer?

% For Hidden_neuron_out<1, Hidden_neuron_in<=5. 
% e.g. tansig(5)=0.9999
% tansig(2)=0.9640
% tansig(1)=0.7616
H=D+sum ( H );

% -no_hidden_neurons<=y_hat<=no_hidden_neurons because -1<=tansig(.)<=1
%             N_h
% and y_hat = sum tansig(.)
%             n=1   
%y_hat= floor( V'*Hidden_neuron_out );
y_hat= V'*H;

% Error calculation
if ( params.opt_input==1 ),
    y_target=board.EVAL_FN(x,y);
    error_y=y_target-y_hat;
elseif ( params.opt_input==2 ),
    % y_target is an integer STRING_SIZE ranges from -string_size_max to string_size_max.
    y_target=board.at(board.time_n).STRING_SIZE(x,y);
    % Error is the difference between the target string size and the
    % estimated string size. Ideally, the error should be an integer.
    % However, it's less likely to happen, so the error should be forced to
    % become an integer. I don't know which one is the best among
    % ceil, floor, and round, but I believe the first two may work just fine
    % as long as either of them is used consistently. 
    % *** Double-check if this definition of error is fine.    
    error_y= y_target-floor(y_hat);
elseif ( params.opt_input==3 ),
    y_target=board.at(board.time_n).STRING_SIZE(x,y)/board.string_size_max;
end;

% Store the values
csrn.srn(x,y).output.At(csrn.time_n)=floor(y_hat);
csrn.srn(x,y).H_neuron_out.At(csrn.time_n,:)=H;
csrn.srn(x,y).error_y.At(csrn.time_n)=error_y;

% Feed back the output as an input 
fb_input_index=csrn.srn(x,y).fb_input_location;
csrn.srn(x,y).Input( fb_input_index )= csrn.srn(x,y).output.At(csrn.time_n);