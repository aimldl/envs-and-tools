% Written by Tae-Hyung D. Kim, tk424@mst.edu
% This project is started on Apr. 8, 2008 (Tue).
% Version: 1.0
% Last updated: May. 22, 2008 (Thu)

% Clear all the previous records and figures
clear all; close all; clc;
cd ..;

% run_simulations(brd_size,opt_nnc,opt_test)
% opt_nnc=1: MLP, 2: SRN, 3: NSRN
% if ( opt_test == 1 ),
%     mm_max=5; nn_max=100; oo_max=20; ii_max=10;
% elseif ( opt_test == 2 ),
%     mm_max=5; nn_max=1000; oo_max=20; ii_max=10;
% elseif ( opt_test == 3 ),
%     mm_max=3; nn_max=1000; oo_max=20; ii_max=10;
% elseif ( opt_test == 4 ),
%     mm_max=3; nn_max=10000; oo_max=20; ii_max=10;
% elseif ( opt_test == 5 ),
%     mm_max=500; nn_max=10000; oo_max=20; ii_max=10;
% end;
run_simulations(3,3,1);