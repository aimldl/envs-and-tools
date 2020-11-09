function generate_input_data( board_max ),

% generate_input_data
%
% Place stones randomly, and generate the input data sets
%
% Last updated: May 28, 2008
% First written: sometime in 2008.
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

bb_now=1;
if (board_max <=6),
    scaler=1;
else,
    % board_max=7 runs virtually forever with scaler=1.
    scaler=0.8;
end;
bb_max=round( scaler.*3.*factorial(board_max) );

disp( sprintf('Progress for %dx%d',board_max,board_max) );
data.input(1).BS=round( 2.*rand(board_max,board_max)-1 );
while ( bb_now<bb_max ),
    is_found=0;
    BB_tmp=round( 2.*rand(board_max,board_max)-1 );
    % Check if BB_tmp is already in data.input(bb).BS
    for bb=1:bb_now,
        if ( data.input(bb).BS==BB_tmp ),
            is_found=1;
            break;
        end;
    end;
    if ( is_found==0 ),
        bb_now=bb_now+1;
        data.input(bb_now).BS=BB_tmp;
    end;
    if ( mod(bb_now,1000)==0 ),
        disp( sprintf('\t%d/%d',bb_now,bb_max) );
    end;
end;
disp('done.');
dir_mat_files='data/mat_files';
file_name=sprintf( '%s/data_input_%dx%d',dir_mat_files,board_max,board_max );
disp( sprintf('Saving to %s ...',file_name) );
save( file_name, 'data');