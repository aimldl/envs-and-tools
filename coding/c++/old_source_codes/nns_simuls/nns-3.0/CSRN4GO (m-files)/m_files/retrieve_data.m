function [board,data]=retrieve_data(board);

% retrieve_data      Generate the input and target data sets
%
% Input data is a Go board status.
% Target data is the number of stones in the same group or string size.
%
% data
%   .input
%   .target
%   .estimate
%   .stats

board_max=board.cfg.size;
scaler=1;
bb_max=round( scaler.*3.*factorial(board_max) );

% Retrieve the input and target data
% data_01 places stones manually.
data.cfg.is_read=0;

dir_mat_files='data/mat_files';
file_name=sprintf( '%s/data_input_%dx%d',dir_mat_files,board_max,board_max );
disp( sprintf('Retrieving data from %s ...',file_name) );
% Assume both data.input and data.target are prepared somewhere else.
load(file_name,'data');

data.cfg.is_read=1;
bb_max=length( data.input );
board.cfg.N_b=bb_max;
for bb=1:bb_max,
    % SS (String Size)
    data.estimate(bb).SS    = zeros( board_max,board_max );
end;