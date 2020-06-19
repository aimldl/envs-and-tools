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

run_simulations(6,2,10);