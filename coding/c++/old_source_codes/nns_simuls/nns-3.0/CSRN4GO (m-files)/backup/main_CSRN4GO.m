% Cellular Simultaneous Recurrent Networks on Game of Go (CSRN4GO)
% CSRN is SRNs in a cellular structure.
%
% Written by Tae-Hyung D. Kim, tk424@mst.edu
% This project is started on Apr. 8, 2008 (Tue).
% Version: 1.0
% Last updated: Apr. 28, 2008 (Mon)
%
% Convention for variable names
%   scalar      all small letters, e.g. is_over
%   vector      the first letter is capitalized, e.g. Input
%   matrix      all large letters, csrn.srn(x,y).scope.POSITION
%   structure   all small letters

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Works to do             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Apr.22, 2008 (Tue)
% Target:
%   Make the simulator learn the target function
%
% 1. Change the structure
%    ==> make another function to compare the results
% 2. Change the fitness function
%    ==> MSE as the fitness function for PSO is not gonna work.
%    ==> Change the codes
% 3. Run the simulator after changes and see if it works.

% Clear all the previous records and figures
clear all; close all; clc;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      Directory Structure          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DATA='data';
M_FILES='m_files';

DIR_PROG_ROOT=pwd;
% For Windows
DIR_DATA=[DIR_PROG_ROOT,'\',DATA];
DIR_M_FILES=[DIR_PROG_ROOT,'\',M_FILES];
% For Linux
DIR_DATA=[DIR_PROG_ROOT,'/',DATA];
DIR_M_FILES=[DIR_PROG_ROOT,'/',M_FILES];

addpath( genpath(DIR_DATA) );
addpath( genpath(DIR_M_FILES) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Simulation parameters       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%
%    Options    %
%%%%%%%%%%%%%%%%%
% 1: random board, 2: , 3: random (test) input data ,4: SSF file
% 3 was implemented once, but outdated.
% So, this needs to be implemented again.
params.opt_input=2;
params.plot_results=0;

board.max_board=2;

params.iteration_max=2;
csrn.time_n_max=1000;      % Number of sweeps to train the entire csrn.
csrn.config.is_display_mse=1;
csrn.config.display_frequency=10;

pso.time_n_max=10;
pso.config.is_display_mse=1;
pso.config.display_frequency=100;

% The prefered search is when csrn.time_n_max >> pso.time_n_max.
% In other words, balancing the CSRN w.r.t. g_fitness by iterating
% at the cell strcture (csrn.time_n).

%%%%%%%%%%%%%%%%%
%  Initialize   %
%%%%%%%%%%%%%%%%%
params=initialize_parameters(params);
board=initialize_board(board);
csrn=initialize_csrn(board);
pso=initialize_pso(board,csrn);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Run Simulations         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Go presents a sequential data, which can be confusing in terms of
% learning. Note that the conventional procedure for learning with NN is
% for only a single board representation!!!

% Selection of time_n_max is critical on simulation run-time.
% In the following setting,
% 	board.time_n=1	board.time_n_max= 1000
% 	csrn.time_n =1	csrn.time_n_max = 10000
% 	pso.time_n  =1	pso.time_n_max  = 1000
% 
% It takes about six hours to run csrn.time_n=114
% when pso.time_n_max is set to 1000 for 9x9 board. 
%
%   21600 secs/114,000 PSO iteration = 0.1895sec/PSO iteration
%

%%%%%%%%%%%%%%%%%
%     Input     %
%%%%%%%%%%%%%%%%%
if ( params.opt_input==1 ),
    board=generate_rand_board(board);
elseif ( params.opt_input==2 ),
    if ( board.max_board==2 ),
        board=generate_test_input_data(board);        
    else,
        % To be replaced...
        board=generate_rand_input_data(board);
    end;
elseif ( params.opt_input==3 ),
    board=generate_rand_input_data(board);
elseif ( params.opt_input==4 ),    
    board=parse_input_files(board);
end;

%%%%%%%%%%%%%%%%%
% Disp. Config. %
%%%%%%%%%%%%%%%%%
if ( params.opt_input==1 ),
    disp('Input type: a random board for testing');
elseif ( params.opt_input==2 ),
    disp('Input type: a random input boards for testing');
elseif ( params.opt_input==3 ),
    disp('Input type: SSF input files');    
end;

disp( sprintf('Board sizew: %dx%d',board.max_board,board.max_board) );

if ( params.plot_results==1 ),
    disp('Plot Results On.');
end;

disp('Three counters (iterators):');
disp( sprintf('\tboard.time_n=%d\tboard.time_n_max= %d',board.time_n,board.time_n_max) );
disp( sprintf('\tcsrn.time_n =%d\tcsrn.time_n_max = %d',csrn.time_n,csrn.time_n_max) );
disp( sprintf('\tpso.time_n  =%d\tpso.time_n_max  = %d',pso.time_n,pso.time_n_max) );
disp(' ');
%%%%%%%%%%%%%%%%%
%     Start     %
%%%%%%%%%%%%%%%%%
disp('Simulation starts...');
params.iteration=1;
% Initialize the SRN outputs
csrn=generate_rand_srn_outputs(board,csrn);

while params.iteration<=params.iteration_max,
    disp( sprintf('params.iteration=%d',params.iteration) );
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    board.time_n=1;
    while board.time_n<=board.time_n_max,
        disp( sprintf('board.time_n=%d',board.time_n) );
        csrn=CSRN4GO_3(board,csrn,params,pso);
        board.time_n=board.time_n+1;
    end;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
    params.iteration=params.iteration+1;
end;
disp('End of the simulation.');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      Plot Simulation Results      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

tmp_time_n_max=114;
Ave_mse=zeros(1,tmp_time_n_max);

% For manual interpretation,
for nn=1:tmp_time_n_max,
    Ave_mse(nn)=csrn.stats.at(nn).ave_mse;
end;
plot(1:tmp_time_n_max,Ave_mse);


if ( params.plot_results==1 ),

    for nn=1:csrn.time_n_max,
        Time_n4csrn(nn) = nn;
        Ave_mse(nn) = csrn.stats.at(nn).ave_mse;
    end;
    plot(Time_n4csrn, Ave_mse);
    grid on; axis on;
    xlabel('CSRN epoch (n)'); 
    ylabel('Average MSE over all the nodes');
    title( sprintf('Ave. MSE for a CSRN') );

    %
    for nn=1:board.time_n_max,
        Time_n4board(nn) = nn;
        Ave_ave_mse(nn) = mean( Ave_mse );
    end;
    plot(Time_n4board, Ave_ave_mse);
    grid on; axis on;
    xlabel('board epoch (n)'); 
    ylabel('Average over average MSE');
    title( sprintf('Ave. MSE for boards') );
end;

csrn.time_n=1;
TMP_STRING_SIZE=zeros(board.max_board,board.max_board);
for x_tmp=1:board.max_board,
    for y_tmp=1:board.max_board,
        TMP_STRING_SIZE(y_tmp,x_tmp)=round( board.string_size_max.*csrn.srn(x_tmp,y_tmp).output.At(csrn.time_n) );
    end;
end;
TMP_STRING_SIZE

% When STRING_SIZE is displayed from y_hat, multiply y_hat by board.string_size_max
% and round/ceil/floor the value to an integer.

% Save workspace variables to disk, just in case.
save csrn4go.mat;