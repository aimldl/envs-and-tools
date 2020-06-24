% run_count_string_size
%
% This script is  
%
% Last updated: May 28, 2008
% First written: sometime in 2008.
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.
%
% You will see an error message if the recursion limit is too small.
%set(0,'RecursionLimit',10^9);

brd_from    = 6;
brd_to      = 6;
opt_display_results = 1;

dir_mat_files='../data/mat_files';
if ( opt_display_results==0 ),
    disp('run_count_string_size');
    for board_max=brd_from:brd_to,
        file_name=sprintf( '%s/data_input_%dx%d',dir_mat_files,board_max,board_max );
        disp( sprintf('Loading %s ...',file_name) );
        load( file_name, 'data');
        bb_max=length( data.input );
        for bb=1:bb_max,
            BOARD_STATUS=data.input(bb).BS;
            STRING_SIZE=count_string_size( BOARD_STATUS,board_max );
            data.target(bb).SS=STRING_SIZE;
        end;
        disp( sprintf('Conversion done for %dx%d',board_max,board_max ) );
        disp( sprintf('Saving to %s ...',file_name) );
        save( file_name, 'data');    
    end;
    disp('Task completed!');
else,
        board_max=brd_from;
        file_name=sprintf( '%s/data_input_%dx%d',dir_mat_files,board_max,board_max );
        disp( sprintf('Loading %s ...',file_name) );
        load( file_name, 'data');
        bb_max=length( data.input );
        for bb=1:bb_max,
            data.input(bb).BS
            data.target(bb).SS
        end;
end;