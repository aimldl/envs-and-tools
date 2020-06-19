function [cmlp,data,e_t]=calculate_cmlp_output3(cmlp,data,e_t,bb,board_max);

% calculate_cmlp_output      Calculate cellular MLP output
%
% Note the difference between Recurrent Networks (RN) and Simultaneous RN (SRN).
% In practice, RN becomes SRN if RN iterates several times.
% At my best knowledge, there exist no contemporary programming language
% that can "simultaneously" feed back the output to the input.

Y_hat = inf*ones( board_max, board_max );
for x=1:board_max,
    for y=1:board_max,
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        U           = cmlp.cell.loc(x,y).U;
        N_n         = cmlp.cell.loc(x,y).N_n;
        W_u         = cmlp.cell.id(N_n-1).W_u;
        W_v         = cmlp.cell.id(N_n-1).W_v';

        H           = tansig( W_u*U );
        V           = floor( W_v*H );
        Y_hat(x,y)  = V;
        
        e_t(1,N_n-1)= e_t(1,N_n-1)+abs( data.target(bb).SS(x,y)-V );
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    end;
end;

cmlp.cell.Y_hat=Y_hat;
data.estimate(bb).SS=Y_hat;

%e_t=e_t+sum( sum(E_y) );