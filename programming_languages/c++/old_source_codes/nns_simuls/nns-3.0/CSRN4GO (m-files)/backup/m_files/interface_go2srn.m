function csrn=interface_go2srn(board,csrn,params,x,y),

% interface_go2srn     Choose the input to the current SRN
%
% 
% [board,csrn]=interface_go2srn(board,csrn)
% For node at (x,y), there exists a corresponding SRN.
% This SRN needs input and output.
% Input to this node [West, North, Center, South, West]
%         (1,2)                        (y-1,x)
% (2,1)   (2,2)   (2,3)      (y,x-1)   (y,x)   (y,x+1)
%         (3,2)                        (y+1,x)

%csrn.srn(x,y).Input=[];
%csrn.srn(x,y).Fb_input=[];


Input_tmp=[];
Fb_input_tmp=[];
IS_SCOPE_TMP=csrn.srn(x,y).scope.IS_SCOPE;

% For debugging
% disp('---------------------');
% [x,y]
% csrn.srn(x,y).scope.IS_SCOPE
% board.STATUS
% csrn.srn(x,y).Input
csrn.srn(x,y).location=[x,y];
% The order to store is center, top, right, down, left (clockwise)
% In this way the center is stored at the very beginning all the time.

% Eventually NN_OUTPUT=TMP_OUTPUT in function generate_rand_srn_outputs
NN_OUTPUT=zeros(board.max_board,board.max_board);
if ( params.opt_input==1 ),
    CURRENT_BOARD=board.at(1).STATUS;
    for x_tmp=1:board.max_board,
        for y_tmp=1:board.max_board,
            NN_OUTPUT(y_tmp,x_tmp)=csrn.srn(x_tmp,y_tmp).v_output;
        end;
    end;
elseif ( params.opt_input==2 ),
    CURRENT_BOARD=board.at(board.time_n).STATUS;
    for x_tmp=1:board.max_board,
        for y_tmp=1:board.max_board,
            NN_OUTPUT(y_tmp,x_tmp)=csrn.srn(x_tmp,y_tmp).v_output;
        end;
    end;
elseif ( params.opt_input==3 ),
    CURRENT_BOARD=board.at(board.time_n).STATUS;
    for x_tmp=1:board.max_board,
        for y_tmp=1:board.max_board,
            NN_OUTPUT(y_tmp,x_tmp)=csrn.srn(x_tmp,y_tmp).v_output;
        end;
    end;
end;

if ( IS_SCOPE_TMP(2,2)==1 ),
    Input_tmp=[Input_tmp, CURRENT_BOARD(y,x) ];
    Fb_input_tmp=[Fb_input_tmp, NN_OUTPUT(y,x)];            
end;
if ( IS_SCOPE_TMP(1,2)==1 ),
    Input_tmp=[Input_tmp, CURRENT_BOARD(y-1,x) ];
    Fb_input_tmp=[Fb_input_tmp, NN_OUTPUT(y-1,x)];            
end;
if ( IS_SCOPE_TMP(2,3)==1 ),
    Input_tmp=[Input_tmp, CURRENT_BOARD(y,x+1) ];
    Fb_input_tmp=[Fb_input_tmp, NN_OUTPUT(y,x+1)];
end;
if ( IS_SCOPE_TMP(3,2)==1 ),
    Input_tmp=[Input_tmp, CURRENT_BOARD(y+1,x) ];
    Fb_input_tmp=[Fb_input_tmp, NN_OUTPUT(y+1,x)];
end;
if ( IS_SCOPE_TMP(2,1)==1 ),
    Input_tmp=[Input_tmp, CURRENT_BOARD(y,x-1) ];
    Fb_input_tmp=[Fb_input_tmp, NN_OUTPUT(y,x-1)];
end;

% Merge the input from the board and the feedback.
% Add noise to the input from the board representation.
% This is necessary because most of the input data is zero, 
% and prohibits learning.
tmp_length=length(Input_tmp);
Input_tmp=Input_tmp+csrn.config.noise_max*( rand( 1, tmp_length )-0.5 );
for jj=1:tmp_length,
    if ( Input_tmp(jj) > 1),
        Input_tmp(jj)=1;
    elseif ( Input_tmp(jj) < -1),
        Input_tmp(jj)=-1;
    end;
end;
% 1 is bias
Input_tmp=[Input_tmp, Fb_input_tmp,1];
csrn.srn(x,y).Input=Input_tmp';
csrn.srn(x,y).input_length=length(csrn.srn(x,y).Input);

% For debugging
% csrn.srn(x,y).Input
