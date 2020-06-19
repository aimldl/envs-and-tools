function csrn=generate_rand_srn_outputs(board,csrn)

% generate_rand_srn_outputs     
%
% SRN's input requires SRN output.
% Use this function to start from random values of SRN output
% Randomize SRN outputs only once at the very beginning.
% At the second iteration, this function is unnecessary and should not be used
% because the SRN outputs already have values.

TMP_OUTPUT=rand(board.max_board,board.max_board);

for x=1:board.max_board,
    for y=1:board.max_board,
        csrn.srn(x,y).output.At(1)=TMP_OUTPUT(y,x);
%        csrn.srn(x,y).output.At(csrn.time_n)=TMP_OUTPUT(y,x);        
    end;
end;
