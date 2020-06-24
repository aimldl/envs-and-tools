% run_generate_input_data
% 
% This script is a wrapper around function generate_input_data.
% Run this script to generate input data sets.
% The run-time depends on the board size.
% For a smaller board, e.g. 2x2 or 4x4, it runs instantly.
% For s larger board, e.g. 8x8 or 9x9, it may take days.
%
% Last updated: May 28, 2008
% First written: sometime in 2008.
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

for bb=8:19,
    generate_input_data( bb );
end;