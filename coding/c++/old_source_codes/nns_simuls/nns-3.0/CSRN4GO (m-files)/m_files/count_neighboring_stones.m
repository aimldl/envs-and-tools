function brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );

% count_neighboring_stones
%
% Count the number of stones in the same group with recurrence.
% x_init and y_init are the initial location of BOARD_DUMMY.
%
% See also 
%
% Last updated: May 28, 2008 (Mon)
% First written: Apr. 8, 2008 (Tue)
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

x_d = brd_struct.x_d;
y_d = brd_struct.y_d;

if ( brd_struct.player==BOARD_DUMMY( x_d,y_d ) && brd_struct.MARK_VISIT(x_d,y_d)~=1 ),
%    brd_struct.string_size=brd_struct.string_size+1;
    % Use of brd_struct.player increments for black and decrements for
    % white.
    brd_struct.string_size=brd_struct.string_size+brd_struct.player;
    
    brd_struct.MARK_VISIT(x_d,y_d)=1;
    % Check the neighbors
    brd_struct.x_d = x_d-1; brd_struct.y_d = y_d;
    brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );
    
    brd_struct.x_d = x_d+1; brd_struct.y_d = y_d;
    brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );
    
    brd_struct.x_d = x_d;   brd_struct.y_d = y_d-1;
    brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );
    
    brd_struct.x_d = x_d;   brd_struct.y_d = y_d+1;
    brd_struct=count_neighboring_stones( BOARD_DUMMY,brd_struct );
    
%    brd_struct.S_SIZE_DUMMY( x_d,y_d ) = brd_struct.string_size;
%else,
    % Exit this function. 
end;