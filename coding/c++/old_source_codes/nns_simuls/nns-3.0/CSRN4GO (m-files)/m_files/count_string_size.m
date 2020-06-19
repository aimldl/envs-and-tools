function STRING_SIZE=count_string_size( BOARD_STATUS,board_max );

% count_string_size     
%
% BOARD_STATUS and STRING_SIZE are a nxn matrix. n is the board size.
% This function reads the current board status, counts the string size
% and returns the string size.
%
% Last updated: May 28, 2008 (Mon)
% First written: Apr. 8, 2008 (Tue)
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

% You will see an error message if the recursion limit is too small.
set(0,'RecursionLimit',10^9);

% Sample board status
% board_max=4;
% if ( board_max==2 ),
%     BOARD_STATUS=[1,1;1 0];
% elseif ( board_max==3 ),
%     BOARD_STATUS=[1,1,1;1 0 1; 1 1 1];
% elseif ( board_max==4 ),
%     BOARD_STATUS=[1,1,1 0;1 0 0 1; 1 1 1 0; 0 0 0 0];
% end;

STRING_SIZE = zeros( board_max,board_max );
BOARD_DUMMY = inf.*ones( board_max+2,board_max+2 );
MARK_VISIT  = BOARD_DUMMY;
BOARD_DUMMY(2:board_max+1,2:board_max+1)=BOARD_STATUS;
MARK_VISIT(2:board_max+1,2:board_max+1) = zeros( board_max,board_max );

% If there is a stone (black:1 or white:-1), count the number of stones in
% the same group.
brd_struct.board_max     = board_max;
brd_struct.BOARD_DUMMY   = BOARD_DUMMY;
brd_struct.MARK_VISIT    = MARK_VISIT;

% Use recursion to count the number of neighbors
for x=1:board_max,
    for y=1:board_max,
        if ( BOARD_DUMMY(x+1,y+1)~=0 ),
            brd_struct.x_d = x+1;
            brd_struct.y_d = y+1;
            brd_struct.string_size  = 0;
            brd_struct.player = BOARD_DUMMY(x+1,y+1); % 1 for black, -1 for white
            brd_struct.MARK_VISIT(2:board_max+1,2:board_max+1) = zeros( board_max,board_max );
            brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );
            STRING_SIZE( x,y ) = brd_struct.string_size;
        end;
    end;
end;
% BOARD_STATUS
% STRING_SIZE