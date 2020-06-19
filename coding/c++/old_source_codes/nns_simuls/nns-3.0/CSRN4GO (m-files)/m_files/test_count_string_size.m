% You will see an error message if the recursion limit is too small.
%set(0,'RecursionLimit',10^9);
%
% Last updated: May 28, 2008 (Mon)
% First written: Apr. 8, 2008 (Tue)
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

% Sample board status
board_max=4;
if ( board_max==2 ),
    BOARD_STATUS=[1,1;1 0];
elseif ( board_max==3 ),
    BOARD_STATUS=[1,1,1;1 0 1; 1 1 1];
elseif ( board_max==4 ),
    BOARD_STATUS=[1,1,1 0;1 0 0 1; 1 1 1 0; 0 0 0 0];
end;

STRING_SIZE=count_string_size( BOARD_STATUS,board_max );