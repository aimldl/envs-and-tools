function run_simulations(varargin);

% run_simulations       Run simulations for a CNN (Cellular Neural Networks)
%
% This m-file stores the options/configuration to run simulations.
% Given these settings, the main function is invoked.
% This function can be thought as a wrapper around the main function.
%
% Usage: 
%   run_simulations(brd_size,opt_nnc,opt_test)
%
%   brd_size ranges from 2 to 19
%   opt_nnc is 1 (MLP),2 (SRN),3 (SRNwHR)
%   opt_test ranges from 1 to 5
%   opt_pso is the option for PSO's design parameters.
%
% e.g. Run simulations with MLP for 3x3 setting. Test option is 2.
%   >> run_simulations(3,1,2,1)
%
% if ( opt_test == 1 ),
%     mm_max=1;   nn_max=10;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 2 ),
%     mm_max=1;   nn_max=100;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 3 ),
%     mm_max=1;   nn_max=1000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 4 ),
%     mm_max=1;   nn_max=10000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 5 ),
%     mm_max=1;   nn_max=100000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 6 ),
%     mm_max=10;  nn_max=100;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 7 ),
%     mm_max=10;  nn_max=1000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 8 ),
%     mm_max=10;  nn_max=10000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 9 ),
%     mm_max=300;  nn_max=1000;
%     oo_max=20;  ii_max=10;
% elseif ( opt_test == 10 ),
%     mm_max=300;  nn_max=100000;
%     oo_max=20;  ii_max=10;
% end;
%
% mm_max Maximum number of iteration to average out, "M"ean 
% nn_max PSO, epochs "n"
% oo_max SRN, "O"uter loop
% ii_max SRN with hidden layer recurrence, "I"nner loop
%
% is_disp=1;  disp_freq=100;  plot_y_scaler=10;
%
% Version: 1.0
%
% See also main_nncs
%
% Last updated: May 22, 2008 (Thu)
% First written: Apr. 8, 2008 (Tue)
%
% Copyright©2008 Tae-Hyung "T" Kim. All rights reserved.
%
% Convention for variable names
%   scalar      all small letters, e.g. is_over
%   vector      the first letter is capitalized, e.g. Input
%   matrix      all large letters, csrn.srn(x,y).scope.POSITION
%   structure   all small letters

if ( nargin == 0 || nargin>4 ),
    disp('Usage: run_simulations(brd_size,opt_nnc,opt_test)');
    disp('brd_size ranges from 2 to 19');
    disp('opt_nnc is 1 (MLP),2 (SRN),3 (NSRN)');
    disp('opt_test ranges from 1 to 5');
    disp('opt_pso is a goupr of options for PSO');
    error('e.g. >> run_simulations(3,1,2,1)');
end;

% User configurable options
% Option for Neural Networks Cells
%    opt_nnc=1: MLP, 2: SRN, 3: NSRN
brd_size    = varargin{1};
opt_nnc     = varargin{2};
opt_test    = varargin{3};
opt_pso     = varargin{4};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Configuration given the options  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
config_08012008;    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         Display Options           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
is_disp=0;
if ( nn_max <1000 || mm_max>50 ),
    disp_freq=nn_max/100;
else,
    disp_freq=nn_max/100;
end;
    plot_y_scaler=10;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Options for saving to a MAT file  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
config_opts=sprintf( '%d-%d-%d-%d',brd_size,opt_nnc,opt_test,opt_pso );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Call main.m to run simulations   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
main_nncs(brd_size,opt_nnc,mm_max,nn_max,oo_max,ii_max,is_disp,disp_freq,plot_y_scaler,pso_size,pso_w,pso_c1,pso_c2,config_opts);