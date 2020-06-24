function csrn=interface_data2csrn(csrn,data,bb,board_max),

% interface_data2csrn   Interface the input and output data sets to CSRN
%                       Board status -> input to CSRN
%                       Target function -> target to CSRN
%
% Input:
% Due to the cellular structure, input to CSRN is a function of
% board status at a location and its neighbors along with their feedback
% output of CSRN.
% In other words, input to a center node at (x,y) is taken from [West,
% North, Center, South, West]
%
% In other setting, a node or a SRN at location (x,y) neighbors with the
% vertical and horizontal nodes, not the diagonal ones. That is,
%
%         (1,2)                        (y-1,x)
% (2,1)   (2,2)   (2,3)      (y,x-1)   (y,x)   (y,x+1)
%         (3,2)                        (y+1,x)
%
% Note x and y used, actually, in a matrix are flipped unlike the conventional notation of (x,y). 
%
% U is the input matrix for CSRN
% V is the output matrix for CSRN

X=data.input(bb).BS;
Y=data.target(bb).SS;
noise_max=csrn.cfg.noise_max;

U=[];
for x=1:board_max,
    for y=1:board_max,
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        U_tmp=[]; V_tmp=[];
        SCOPE=csrn.srn.loc(x,y).SCOPE;
        if ( SCOPE(2,2)==1 ),
            U_tmp=[U_tmp, X(y,x) ];
            V_tmp=[V_tmp, Y(y,x)];            
        end;
        if ( SCOPE(1,2)==1 ),
            U_tmp=[U_tmp, X(y-1,x) ];
            V_tmp=[V_tmp, Y(y-1,x)];            
        end;
        if ( SCOPE(2,3)==1 ),
            U_tmp=[U_tmp, X(y,x+1) ];
            V_tmp=[V_tmp, Y(y,x+1)];
        end;
        if ( SCOPE(3,2)==1 ),
            U_tmp=[U_tmp, X(y+1,x) ];
            V_tmp=[V_tmp, Y(y+1,x)];
        end;
        if ( SCOPE(2,1)==1 ),
            U_tmp=[U_tmp, X(y,x-1) ];
            V_tmp=[V_tmp, Y(y,x-1)];
        end;

        % Merge the input from the board and the feedback.
        % Add noise to the input from the board representation.
        % This is necessary because most of the input data is zero, 
        % and prohibits learning.
        tmp_length=length(U_tmp);
        U_tmp=U_tmp+noise_max*( rand( 1, tmp_length )-0.5 );
        for kk=1:tmp_length,
            if ( U_tmp(kk) > 1),
                U_tmp(kk)=1;
            elseif ( U_tmp(kk) < -1),
                U_tmp(kk)=-1;
            end;
        end;
        % 1 is bias
        U_tmp=[U_tmp, V_tmp,1];
        U=[U,U_tmp'];
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    end;
end;
csrn.srn.U=U;
