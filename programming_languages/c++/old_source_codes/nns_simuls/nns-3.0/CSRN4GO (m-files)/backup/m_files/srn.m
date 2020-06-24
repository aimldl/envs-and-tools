function csrn=SRN(board,csrn,params,x,y)
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

csrn=ffnn(board,csrn,params,x,y);

% Feed back the output as an input 
fb_input_index=csrn.srn(x,y).fb_input_location;
csrn.srn(x,y).Input( fb_input_index )= csrn.srn(x,y).output.At(csrn.time_n);