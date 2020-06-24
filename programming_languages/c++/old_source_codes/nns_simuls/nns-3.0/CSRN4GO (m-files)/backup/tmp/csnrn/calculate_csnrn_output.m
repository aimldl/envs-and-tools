function cnns=calculate_csnrn_output(cnns,board_max,oo_max);

% calculate_csnrn_output      Calculate cellular SRN output
%
% Note the difference between Recurrent Networks (RN) and Simultaneous RN (SRN).
% In practice, RN becomes SRN if RN iterates several times.
% At my best knowledge, there exist no contemporary programming language
% that can "simultaneously" feed back the output to the input.

U           = cnns.cell.U;
W_u         = cnns.cell.W_u;
W_h         = cnns.cell.W_h;
W_v         = cnns.cell.W_v';
N_h         = cnns.cfg.N_h;
D=tansig( W_u*U );
for ss=1:board_max.*board_max,
    tmp_D=[D(:,ss)';ones(size(D(:,ss)'))];
    H_i=[];
    for jj=1:N_h,
        H_i=[H_i,H_o];
    end;
    H_i=[H_i;tmp_D];
    H_o=diag( W_h*H_i );
    % Output layer
    % Activation function for the output layer is floor.
    V(:,ss)= floor( W_v*H_o );
end;


%V           = floor( W_v*H );
%U(1,:)      = V;                % Recurrence
%Y_hat       = reshape( V,board_max, board_max );

%cnns.cell.Y_hat=Y_hat;