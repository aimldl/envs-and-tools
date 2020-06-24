function csrn=calculate_csrn_output(csrn,board_max,oo_max);

% calculate_csrn_output      Calculate cellular SRN output
%
% Note the difference between Recurrent Networks (RN) and Simultaneous RN (SRN).
% In practice, RN becomes SRN if RN iterates several times.
% At my best knowledge, there exist no contemporary programming language
% that can "simultaneously" feed back the output to the input.

U           = csrn.cell.U;
W_u         = csrn.cell.W_u;
W_v         = csrn.cell.W_v';

for oo=1:oo_max,
    H           = tansig( W_u*U );
    V           = floor( W_v*H );
    U(1,:)      = V;                % Recurrence
%    disp( sprintf('oo=%d\t[%d,%d,%d,%d]',oo,V(1),V(2),V(3),V(4)));
end;
Y_hat       = reshape( V,board_max, board_max );

csrn.cell.Y_hat=Y_hat;