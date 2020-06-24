function cnns=interface_data2cnns3(cnns,data,bb_indx,board_max),

% interface_data2cnns   Interface the input and output data sets to CNNS
%                       (Cellular Neural Networks System).
%                       Board status -> input to CNNS
%                       Target function -> target to CNNS
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

X=data.input(bb_indx).BS;
Y=data.target(bb_indx).SS;
noise_max=cnns.cfg.noise_max;

for x=1:board_max,
    for y=1:board_max,
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        U=[]; U_tmp=[]; V_tmp=[];
        SCOPE=cnns.cell.loc(x,y).SCOPE;
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
        for jj=1:tmp_length,
            if ( U_tmp(jj) > 1),
                U_tmp(jj)=1;
            elseif ( U_tmp(jj) < -1),
                U_tmp(jj)=-1;
            end;
        end;
        % 1 is bias
        U_tmp=[U_tmp, V_tmp,1];
        U=[U,U_tmp'];
        cnns.cell.loc(x,y).U=U;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    end;
end;
