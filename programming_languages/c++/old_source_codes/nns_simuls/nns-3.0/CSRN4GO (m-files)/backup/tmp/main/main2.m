% Cellular Simultaneous Recurrent Networks on Game of Go (CSRN4GO)
% CSRN is SRNs in a cellular structure.
%
% main.m for board size of 2.
%
% Written by Tae-Hyung D. Kim, tk424@mst.edu
% This project is started on Apr. 8, 2008 (Tue).
% Version: 1.0
% Last updated: May. 15, 2008 (Thu)
%
% Convention for variable names
%   scalar      all small letters, e.g. is_over
%   vector      the first letter is capitalized, e.g. Input
%   matrix      all large letters, csrn.srn(x,y).scope.POSITION
%   structure   all small letters
%
% This main.m is designed to be run by another m-file called
% "run_scenario". e.g. run_srn or run_mlp
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Recommend to write a run file   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    Directory Structure & Paths    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Add paths necessary to run this m-file.
DATA='data';
M_FILES='m_files';
DIR_PROG_ROOT=pwd;
DIR_DATA=[DIR_PROG_ROOT,'/',DATA];
DIR_M_FILES=[DIR_PROG_ROOT,'/',M_FILES];
addpath( genpath(DIR_DATA) );
addpath( genpath(DIR_M_FILES) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Initialize simulation parameters %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
simul.cfg.plot.y_scaler=plot_y_scaler;
simul.cfg.opt_nnc=opt_nnc;
simul.cfg.nn_max=nn_max;
simul.cfg.scaler=plot_y_scaler;

if isempty(brd_size),
    disp('brd_size is not specified; using the default board size of 2.');
    disp('Use of a run file is recommended.');
    board=init_board();
else
    board=init_board(brd_size);
end;

if ( opt_nnc==1 ),
    nnc_type='mlp';
    nns=init_cmlp(board);
elseif ( opt_nnc==2 ),
    nnc_type='srn';
    nns=init_csrn(board,oo_max);
elseif ( opt_nnc==3 ),
    % Simultaneous Nested Recurrence (Networks)
    nnc_type='snr';
    nns=init_csnrn(board,oo_max,ii_max);
end;
simul.cfg.nnc_type=nnc_type;

pso=config_pso(board,nns,nn_max,nnc_type);
% E_T is a dummy variable for rec.e_t.
E_T=zeros( mm_max,nn_max );
rec.e_t=zeros(1,nn_max);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Input               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[board,data]=get_input_target_data(board);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Run Simulations         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp( sprintf('Board size: %dx%d',board.cfg.size,board.cfg.size) );
disp('Simulation starts...');

fitness_t=pso.cfg.p.target_fitness;
for mm=1:mm_max,
    % Initialize
    nn=1;
    pso=init_pso(pso);
    fitness_g=pso.p.g_fitness;
    % Initialize
    while ( (nn<=nn_max) && (fitness_g>=fitness_t) ),
        if ( mod(mm,disp_freq)==1 && mod(nn,disp_freq)==1 && is_disp==1 ),
            disp( sprintf('mm=%d\tn=%d',mm,nn) );        
        end;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        [data,nns,pso]=update_pso2(board,nns,data,pso,nn,simul.cfg.nnc_type);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if ( mod(mm,disp_freq)==1 && mod(nn,disp_freq)==1 && is_disp==1 ),
            disp( sprintf('e_t=%d',pso.p.g_fitness) );
        end;
        E_T(mm,nn) = pso.p.g_fitness;
        fitness_g=pso.p.g_fitness;
        nn=nn+1;
    end;
end;
disp('End of the simulation.');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      Postprocess simulations      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
rec.e_t=mean(E_T);
plot_learning_curve(rec,simul);