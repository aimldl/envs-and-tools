function main_nncs(varargin);

% main_nncs     Main function for Neural Networks in Cellular Structure
%
% This main.m is designed to be invoked by another function run_simulations
%
% Version: 1.0
%
% See also run_simulations
%
% Last updated: May 22, 2008 (Thu)
% First written: Apr. 8, 2008 (Tue)
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.

% Convention for variable names
%   scalar      all small letters, e.g. is_over
%   vector      the first letter is capitalized, e.g. Input
%   matrix      all large letters, csrn.srn(x,y).scope.POSITION
%   structure   all small letters

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    Directory Structure & Paths    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Add paths necessary to run this m-file.
DATA='data';
M_FILES='m_files';
DIR_PROG_ROOT=pwd;
DIR_DATA=[DIR_PROG_ROOT,'/',DATA];
DIR_M_FILES=[DIR_PROG_ROOT,'/',M_FILES];
DIR_MAT_FILES='data/mat_files/simulations';
addpath( genpath(DIR_DATA) );
addpath( genpath(DIR_M_FILES) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Variables               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
brd_size                = varargin{1};
opt_nnc                 = varargin{2};
mm_max                  = varargin{3};
nn_max                  = varargin{4};
oo_max                  = varargin{5};
ii_max                  = varargin{6};
is_disp                 = varargin{7};
disp_freq               = varargin{8};
y_scaler                = varargin{9};
pso_size                = varargin{10};
pso_w                   = varargin{11};
pso_c1                  = varargin{12};
pso_c2                  = varargin{13};
config_opts             = varargin{14};

simul.cfg.nn_max        = nn_max;
simul.cfg.plot.y_scaler = y_scaler;
simul.cfg.opt_nnc       = opt_nnc;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Initialize simulation parameters %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
board=init_board(brd_size);

if ( opt_nnc==1 ),
    nnc_type='mlp';
    nns=init_cmlp(board);
elseif ( opt_nnc==2 ),
    nnc_type='srn';
    nns=init_csrn(board,oo_max);
elseif ( opt_nnc==3 ),
    % Nested Simultaneous Recurrent (Networks)
    nnc_type='nsr';
    nns=init_cnsrn(board,oo_max,ii_max);
end;
simul.cfg.nnc_type=nnc_type;

%pso=config_pso(board,nns,nn_max,nnc_type);
pso=config_pso(board,nns,nn_max,nnc_type,pso_size,pso_w,pso_c1,pso_c2);
% E_T is a dummy variable for rec.e_t.
E_T=zeros( mm_max,nn_max );
rec.e_t=zeros(1,nn_max);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Input               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%[board,data]=get_input_target_data(board);
[board,data]=retrieve_data(board);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%              Output               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
output_dir_name  = sprintf( '%s/%dx%d',DIR_MAT_FILES,brd_size,brd_size );
output_file_name = sprintf( '%s-%s',nnc_type,config_opts );
output_file = sprintf( '%s/%s',output_dir_name,output_file_name);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Run Simulations         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp( sprintf('Board size: %dx%d',board.cfg.size,board.cfg.size) );
disp( sprintf('NN Cell Type: %s',nnc_type) );
disp( sprintf('mm_max: %d',mm_max) );
disp( sprintf('nn_max: %d',nn_max) );
disp( sprintf('oo_max: %d',oo_max) );
disp( sprintf('ii_max: %d',ii_max) );
disp('Simulation starts...');

fitness_t=pso.cfg.p.target_fitness;
for mm=1:mm_max,
    % Initialize
    nn=1;
    pso=init_pso(pso,nns.cell.N_n_max);
    fitness_g=pso.p.g_fitness;
    % is_cont stands for "is continue?". One of the stopping criteria.
%    is_cont=( (pso.p.id(1).g_fitness>=fitness_t) && (pso.p.id(2).g_fitness>=fitness_t) && (pso.p.id(3).g_fitness>=fitness_t) );
    % Initialize
    while ( (nn<=nn_max) && (fitness_g>=fitness_t) ),
%    while ( (nn<=nn_max) && (is_cont) ),
        if ( mod(mm,disp_freq)==1 && mod(nn,disp_freq)==1 && is_disp==1 ),
            disp( sprintf('mm=%d\tn=%d',mm,nn) );        
        end;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        [data,nns,pso]=update_pso(board,nns,data,pso,nn,simul.cfg.nnc_type);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        fitness_g = pso.p.g_fitness;
        E_T(mm,nn) = fitness_g;
        if ( mod(mm,disp_freq)==1 && mod(nn,disp_freq)==1 && is_disp==1 ),
            disp( sprintf('e_t=%d',fitness_g) );
%            disp( sprintf('Saving to %s ...',output_file) );
            save( output_file );
        end;
        nn=nn+1;
    end;
end;
% The last display
disp( sprintf('mm=%d\tn=%d',mm,nn) );        
disp( sprintf('e_t=%d',fitness_g) );
disp('End of the simulation.');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      Postprocess simulations      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if ( mm_max==1 ),
    rec.e_t=E_T;
else,
    rec.e_t=mean(E_T);
end;
disp( sprintf('Saving all the variables to %s...',output_file) );
save( output_file );
plot_learning_curve(rec,simul,brd_size,output_dir_name,output_file_name);