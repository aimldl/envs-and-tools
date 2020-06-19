% This script is designed to set up a path for CSRN4GO.
%
% This can be run when Matlab is run in console mode, e.g. on Linux/Sun
% servers.
%
% Last updated: May. 29, 2008 (Thu)
% First written: May. 29, 2008 (Thu)

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