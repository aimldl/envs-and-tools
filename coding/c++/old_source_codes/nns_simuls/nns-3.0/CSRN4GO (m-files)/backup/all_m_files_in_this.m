function board=initialize_board(),
% A function to initialize structure board
%
% Initialize the current board representation
% EMPTY: 0, BLACK: 1, WHITE: -1
% player: black 1, white -1
board.player=1;
board.time_n=1;
% Set this value to 0, then it doesn't run without input data.
board.time_n_max=0;
board.max_board=4;
board.STATUS=zeros(board.max_board,board.max_board);
% Evaluation function is the target for CSRN.
% Initialize it with random numbers.
board.EVAL_FN=rand(board.max_board,board.max_board);


function csrn=initialize_csrn(board),
% initialize_csrn   initialize a structure csrn 
%                   CSRN (Cellular Simultaneous Recurrent Networks)
%
% Initialize the weight matrix W
% Each row of the weight matrix W corresponds to a layer 
% in the Neural Networks (NNs) or NeuralNets.
%
% The number of Neurons differs from node to node depending on the location.
% - Nodes at the edges of the Go board
%   They have two neighboring nodes, so three neurons (including itself) 
%   are necessary to consider the current board status.
%   The feedback part doubles the size of the required neurons.
%   So six neurons are necessary in total. In other words,
%   Number of neighboring nodes: 2
%   Number of neurons: (N_neighbor+1)x2=6
% - Along the border of the Go board except the edges
%   Number of neighboring nodes: 3
%   Number of neurons: (N_neighbor+1)x2=8
% - The rest of nodes on the board
%   Number of neighboring nodes: 4
%   Number of neurons: (N_neighbor+1)x2=10
%   
% So, the usage should be
% board=initialize_board();
% csrn=initialize_csrn(board);
%
% structure board should be initialized earlier.
% ??? Undefined variable "board" or class "board.max_board".
% 
% Error in ==> initialize_csrn at 27
% csrn.config.struct=[board.max_board, board.max_board];    % row-by-column structure
% 
% Error in ==> main_CSRN4GO at 55
% csrn=initialize_csrn();

% Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
csrn.config.No_neurons=[3,1];

% Initialize the weight matrix
for x=1:board.max_board,
    for y=1:board.max_board,
        if ( (x==1 && y==1)||(x==1 && y==board.max_board) || (x==board.max_board && y==1) ||(x==board.max_board && y==board.max_board) ),
            csrn.srn(x,y).no_neighbors=2;
        elseif ( x==1 || y==1 || x==board.max_board || y==board.max_board),
            csrn.srn(x,y).no_neighbors=3;
        else,
            csrn.srn(x,y).no_neighbors=4;
        end;
        % Initialize the weights
        % To randomize the weights, the training algorithm, e.g. PSO,
        % should map the randomized initial values to NN weights!
        %
        % csrn.config.No_neurons(1): Number of neurons at layer 1
        % csrn.config.No_neurons(2): Number of neurons at layer 2
        %
        % Later, csrn.srn(x,y).input_lengh, csrn.srn(x,y).Input, and
        % csrn.srn(x,y).Input2nn will be computed.
        %    csrn.srn(x,y).input_lengh=length(csrn.srn(x,y).Input);
        %    csrn.srn(x,y).Input2nn=[csrn.srn(x,y).Input,1];
        % The relationship between these variables & "csrn.srn(x,y).no_neighbors+1"
        % is as follows.
        %    csrn.srn(x,y).input_lengh=(csrn.srn(x,y).no_neighbors+1)*2;
        %    length(csrn.srn(x,y).Input2nn)
        %   =csrn.srn(x,y).input_lengh+1
        %   =(csrn.srn(x,y).no_neighbors+1)*2+1
        csrn.srn(x,y).input2nn_lengh=(csrn.srn(x,y).no_neighbors+1)*2+1;
        csrn.srn(x,y).W=zeros( csrn.config.No_neurons(1),csrn.srn(x,y).input2nn_lengh );
        csrn.srn(x,y).V=zeros( csrn.config.No_neurons(2),csrn.config.No_neurons(1) );
    end;
end;

% Initialize the scope of SRNs
x_max=board.max_board+2;
y_max=board.max_board+2;
board_dummy=zeros(x_max,y_max);
for x=1:x_max,
    for y=1:y_max,
        if ( x==1 || y==1 || x==x_max || y==y_max ),
            % Mark the out-of-boundary position to infinity
            board_dummy(x,y)=inf;
        end;
    end;
end;

% x and y correspond to column and row, respectively.
% Note it's not row and column.

for x=1:board.max_board,
    % Mark the boundary on the board
    for y=1:board.max_board,
        csrn.srn(x,y).scope.IS_SCOPE=board_dummy(y:y+2,x:x+2);
        % Mark the scope
        %         (1,2)
        % (2,1)   (2,2)   (2,3)
        %         (3,2)
        if (csrn.srn(x,y).scope.IS_SCOPE(2,1)~=inf),
            csrn.srn(x,y).scope.IS_SCOPE(2,1)=1;
        end;        
        if (csrn.srn(x,y).scope.IS_SCOPE(1,2)~=inf),
            csrn.srn(x,y).scope.IS_SCOPE(1,2)=1;            
        end;        
        if (csrn.srn(x,y).scope.IS_SCOPE(3,2)~=inf),
            csrn.srn(x,y).scope.IS_SCOPE(3,2)=1;            
        end;        
        if (csrn.srn(x,y).scope.IS_SCOPE(2,3)~=inf),
            csrn.srn(x,y).scope.IS_SCOPE(2,3)=1;            
        end;
        csrn.srn(x,y).scope.IS_SCOPE(2,2)=1;
    end;    
end;


function params=initialize_parameters(board),
% A function to initialize structure parameters
%

params.epoch_max=100;
params.epoch=0;
params.iter_opt=1;
params.no_updates_max=100;
% All the nodes on the board should maintain the error curve.
params.ERROR_CURVE=zeros( params.epoch_max,board.max_board,board.max_board);


function pso=initialize_pso(board,csrn),
% initialize_pso        Initialize PSO (Particle Swarm Intelligence)
%
%    Usage: this function should be called after initializing board and
%    csrn.
%           board=initialize_board();
%           csrn=initialize_csrn(board);
%           pso=initialize_pso(board,csrn);
%
% Velocity update equation 
% The velocity update equation (1) is comprised of:
%    inertia of the previous velocity, 
%    the cognitive acceleration term, and 
%    the social acceleration term. 
% This velocity is moving towards both to the local best of the given particle and the global best positions of the whole population. 
%
% The location update equation (2) updates the location of the given particle using the velocity update equation.
%
% P/p   particle
% G/g   global
% L/l   location
% V/v   velocity

pso.config.w=0.8;
pso.config.c1=2;
pso.config.c2=2;
pso.config.target_fitness=10^-3;
pso.config.l_id_max=2.0;
pso.config.v_id_max=100;

for x=1:board.max_board,
    for y=1:board.max_board,
        pso.particles(x,y).size=5;                  % Number of particles        
        [row_W,clmn_W] = size( csrn.srn(x,y).W );
        [row_V,clmn_V] = size( csrn.srn(x,y).V );
        pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
        % Initialize parameters of the PSO algorithm for a node at (x,y)
        % Note these matrice will be expanded as "pso.particles(x,y).size"
        % is expanded.
        pso.particles(x,y).P_BEST = zeros( pso.particles(x,y).dimension,pso.particles(x,y).size );
        pso.particles(x,y).G_BEST = zeros( pso.particles(x,y).dimension,1 );
        pso.particles(x,y).P_fitness = zeros( 1,pso.particles(x,y).size );
        % An arbitrary number large enough to update the global best at the
        % beginning of the iteration. The following condition is in mind.
        % if ( pso.particles(x,y).g_fitness > min(pso.particles(x,y).P_fitness) )
        pso.particles(x,y).g_fitness = 10^6;        
        pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
        pso.particles(x,y).V_ID=rand( size(pso.particles(x,y).L_ID) );
    end;
end;


function board=generate_rand_board(board),

board.STATUS=floor(3.*rand(board.max_board,board.max_board))-1;

% Cellular Simultaneous Recurrent Networks on Game of Go (CSRN4GO)
% CSRN is SRNs in a cellular structure.
%
% Written by Tae-Hyung D. Kim, tk424@mst.edu
% This project is started on Apr. 8, 2008 (Tue).
% Version: 1.0
% Last updated: Apr. 10, 2008 (Thu)
%
% Convention
%   scalar      all small letters, e.g. is_over
%   vector      the first letter is capitalized, e.g. 
%   matrix      all large letters, csrn.srn(x,y).scope.POSITION
%   structure   all small letters

% Clear all the previous records and figures
clear all; close all; clc;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%      Directory Structure          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DATA='data';
M_FILES='m_files';

DIR_PROG_ROOT=pwd;
DIR_DATA=[DIR_PROG_ROOT,'\',DATA];
DIR_M_FILES=[DIR_PROG_ROOT,'\',M_FILES];

addpath( genpath(DIR_DATA) );
addpath( genpath(DIR_M_FILES) );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         Input & Output            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
load 276538.ngi

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Simulation parameters       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%
%   Options     %
%%%%%%%%%%%%%%%%%
optPlotFig=1;                               % Options for plotting figures
testPlots=1;
is_over=0;

%%%%%%%%%%%%%%%%%
%   Config.     %
%%%%%%%%%%%%%%%%%
% Note that input to a NN should be [-1,1];

%%%%%%%%%%%%%%%%%
%  Initialize   %
%%%%%%%%%%%%%%%%%
board=initialize_board();
csrn=initialize_csrn(board);
params=initialize_parameters(board);
pso=initialize_pso(board,csrn);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Run Simulations         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% This is from an input file
%move_seq=X276538;

%board.time_n_max=length(move_seq);
% Go presents a sequential data, which can be confusing in terms of
% learning. Note that the conventional procedure for learning with NN is
% for only a single board representation!!!

board.time_n=1;                % A redundant line for a better readability
board=generate_rand_board(board);
board.time_n_max=2;
disp('Simulation starts...');
while board.time_n<=board.time_n_max,
%     if ( move_seq(board.time_n,1)>0 && move_seq(board.time_n,2)>0 ),
%     % Pass in play is mistranslated into negative values,
%     % so skipping those moves in negative value.
%         board=place_a_stone_at(move_seq(board.time_n,:), board);
%     end;
    csrn=CSRN4GO(board,csrn,params,pso);
    board.time_n=board.time_n+1;
end;
disp('End of the simulation.');


function csrn=CSRN4GO(board,csrn,params,pso)
% CSRN4GO   Cellular Simultaneous Recurrent Networks for Go
%
% CSRN is a bunch of SRNs in cellular structure. In this case,
% we assume this cellular structure matches the structure of a Go board.
% Imagine a node is located at an intersection on a 9x9 Go board.
% These nodes on the board are inter-connected just like the Go board.
% In CSRN, each node corresponds to a SRN.
% This function includes the training part.

% Iteration for the simultaneous part

% The notation may be a little bit confusing.
% A position (x,y) in a catesian coordinate corresponds to [column, row] in a matrix.
% For example, a stone at (1,2) on the board is stored in
% board.STATUS(2,1). In other words, the second row and first column in a
% matrix board.STATUS should be read in order to retrieve data at (1,2) on
% the board. Visually,
%
%    1 2  3
%  1
%  2 X 
%  3
% time_n is time n to play Go. Obviously, n is discrete time index.
% ii indicates the epochs of simulation run. "i" for iteration, but "i" is
% already taken in Matlab. So, "ii" instead of "i".

% A design issue has lots of options.
%    How to iterate, how to compute the target fitness, and so on.
%    Try out this and that.
ii=0;
while ( (ii<params.no_updates_max) ),
    disp_ii=sprintf('Updating CSRN: %d',ii);
    disp(disp_ii);
    csrn=update_CSRN(board,csrn,params,pso);
    ii=ii+1;
end;

function csrn = update_CSRN(board,csrn,params,pso)
% update_CSRN     Update CSRN once
%
% A single sweep or update of CSRN corresponds to an update of all the SRNs
% in the cellular structure. An update of a SRN means a multiple number of
% updates within the SRN. In other words, the output of the FFNN in the SRN
% fed back to the input to the FFNN is updated a multiple number of times.
%
% The following double loop covers the cellular structure of this CSRN
% In other words, a single node corresponds to a single SRN in the loop, and
% visiting all the nodes through the loop (x and y) is a single sweep of a
% CSRN update.

for x=1:board.max_board,
    for y=1:board.max_board,
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
         params.epoch=1;
         csrn=map_input2SRN(board,csrn,x,y);
         while ( (params.epoch<=params.epoch_max) && (pso.particles(x,y).g_fitness>=pso.config.target_fitness) ),
             for pp=1:pso.particles(x,y).size,
                 csrn=map_pso2nnweights(csrn,pso,x,y,pp);
                 csrn=SRN(board,csrn,x,y);
                 [csrn,pso]=pso_update_local_best(board,csrn,params,pso,x,y,pp);
             end;
             [csrn,pso]=pso_update_global_best(board,csrn,params,pso,x,y,pp);
             [csrn,pso]=pso_update_equations(board,csrn,params,pso,x,y,pp);
             params.epoch=params.epoch+1;
          end;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
    end;
end;


function csrn=map_input2SRN(board,csrn,x,y),

% map_input2SRN     Choose the input to the current SRN
%
% 
% [board,csrn]=map_input2SRN(board,csrn)
% For node at (x,y), there exists a corresponding SRN.
% This SRN needs input and output.
% Input to this node [West, North, Center, South, West]
%         (1,2)                        (y-1,x)
% (2,1)   (2,2)   (2,3)      (y,x-1)   (y,x)   (y,x+1)
%         (3,2)                        (y+1,x)

csrn.srn(x,y).Input=[];
csrn.srn(x,y).Fb_input=[];
% For debugging
% disp('---------------------');
% [x,y]
% csrn.srn(x,y).scope.IS_SCOPE
% board.STATUS
% csrn.srn(x,y).Input
csrn.srn(x,y).location=[x,y];
% The order to store is center, top, right, down, left (clockwise)
% In this way the center is stored at the very beginning all the time.
if ( csrn.srn(x,y).scope.IS_SCOPE(2,2)==1 ),
    csrn.srn(x,y).Input=[csrn.srn(x,y).Input, board.STATUS(y,x) ];
    csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y,x)];            
end;
if ( csrn.srn(x,y).scope.IS_SCOPE(1,2)==1 ),
    csrn.srn(x,y).Input=[csrn.srn(x,y).Input, board.STATUS(y-1,x) ];
    csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y-1,x)];            
end;
if ( csrn.srn(x,y).scope.IS_SCOPE(2,3)==1 ),
    csrn.srn(x,y).Input=[csrn.srn(x,y).Input, board.STATUS(y,x+1) ];
    csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y,x+1)];
end;
if ( csrn.srn(x,y).scope.IS_SCOPE(3,2)==1 ),
    csrn.srn(x,y).Input=[csrn.srn(x,y).Input, board.STATUS(y+1,x) ];
    csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y+1,x)];
end;
if ( csrn.srn(x,y).scope.IS_SCOPE(2,1)==1 ),
    csrn.srn(x,y).Input=[csrn.srn(x,y).Input, board.STATUS(y,x-1) ];
    csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y,x-1)];
end;

% Merge the input from the board and the feedback.
csrn.srn(x,y).Input=[csrn.srn(x,y).Input, csrn.srn(x,y).Fb_input];
csrn.srn(x,y).input_lengh=length(csrn.srn(x,y).Input);

% Prepare a NN input earlier. This can actually be redundant.
bias=1;
csrn.srn(x,y).Input2nn=[csrn.srn(x,y).Input, bias]';

% For debugging
% csrn.srn(x,y).Input


function csrn=map_pso2nnweights(csrn,pso,x,y,pp);
% map_pso2nnweights     Map a PSO particle's location to Neural Nets weights
%
% pp particle_index
%         [row_W,clmn_W] = size( csrn.srn(x,y).W );
%         [row_V,clmn_V] = size( csrn.srn(x,y).V );
%         pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%         pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%
%
%   Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
%   csrn.config.No_neurons=[3,1];
%   csrn.srn(x,y).W=rand( csrn.config.No_neurons(1),csrn.srn(x,y).input2nn_lengh );
%   csrn.srn(x,y).V=rand( csrn.config.No_neurons(2),csrn.config.No_neurons(1) );

% When X(:,1) is a 24x1 row vector
% reshape(X(:,1),3,8)
TMP=reshape( pso.particles(x,y).L_ID(:,pp), csrn.config.No_neurons(1), csrn.srn(x,y).input2nn_lengh+csrn.config.No_neurons(2));
csrn.srn(x,y).W=TMP(:,1:csrn.srn(x,y).input2nn_lengh);
csrn.srn(x,y).V=TMP(:,csrn.srn(x,y).input2nn_lengh+1:csrn.srn(x,y).input2nn_lengh+csrn.config.No_neurons(2));

function csrn=SRN(board,csrn,x,y)
% SRN       A module for Simultaneous Recurrent Network
%
% How the SRN structure is constrcuted.
%
%    This SRN module contains a FFNN (Feed-forward Neural Networks).
%    The FFNN's output is fed back as input to the FFNN, and this constructs a
%    Recurrent Network structure.
%    This feedback is iterated a multiple number of times, which constitutes a
%    Simultaneous Recurrent Network structure.
%
% The training algorithm is incorporated into this module.
%    The reason is because the weights of the FFNN should be updated as the
%    FFNN output is iteratively fedback to its input.

csrn=ffnn(board,csrn,x,y);
% Feed back the output as an input 
% csrn.srn(x,y).Fb_input=[csrn.srn(x,y).Fb_input, board.EVAL_FN(y,x+1)];
% csrn.srn(x,y).Input=[csrn.srn(x,y).Input, csrn.srn(x,y).Fb_input];
% csrn.srn(x,y).output
bias=1;
fb_input_length=length(csrn.srn(x,y).Fb_input);
csrn.srn(x,y).Fb_input=[csrn.srn(x,y).output, csrn.srn(x,y).Fb_input(2:fb_input_length)];
csrn.srn(x,y).Input=[csrn.srn(x,y).Input(1:fb_input_length), csrn.srn(x,y).Fb_input];
csrn.srn(x,y).Input2nn=[csrn.srn(x,y).Input, bias]';

function csrn=ffnn(board,csrn,x,y)
% ffnn      Feed-Forward Neural Networks in the sequential mode
%
% A function for MLP (Multi-Layer Perceptron)
% I have to use sequential mode training, not batch mode training because 
% stones in Go are presented sequentially.

% Variable mapping.
U=csrn.srn(x,y).Input2nn;
W=csrn.srn(x,y).W;
V=csrn.srn(x,y).V;
ttl_no_input=csrn.srn(x,y).input2nn_lengh;
y_target=board.EVAL_FN(x,y);

% Compute the output
D=logsig(W*U);
y_hat=V'*D;

% Error calculation
error_y=y_target-y_hat;
mse=sum(error_y.^2)./ttl_no_input;

% Store the values
csrn.srn(x,y).Output_layer_1=D;
csrn.srn(x,y).output=y_hat;
csrn.srn(x,y).Error(board.time_n)=error_y;
csrn.srn(x,y).Mse(board.time_n)=mse;

function [csrn,pso]=pso_update_local_best(board,csrn,params,pso,x,y,pp)

%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.particles(x,y).size=5;                  % Number of particles        
%     [row_W,clmn_W] = size( csrn.srn(x,y).W );
%     [row_V,clmn_V] = size( csrn.srn(x,y).V );
%     pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%     % Initialize parameters of the PSO algorithm for a node at (x,y)
%     % Note these matrice will be expanded as "pso.particles(x,y).size"
%     % is expanded.
%     pso.particles(x,y).P_BEST = zeros( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).G_BEST = zeros( pso.particles(x,y).dimension,1 );
%     pso.particles(x,y).P_fitness = zeros( 1,pso.particles(x,y).size );
%     pso.particles(x,y).g_fitness = 10^6;
%     pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).V_ID=rand( size(pso.particles(x,y).L_ID) );

% Update the local best or particel best, i.e. pso.particles(x,y).P_BEST

if ( (pso.particles(x,y).P_fitness(1,pp)==0) && (params.epoch==1) ),
    pso.particles(x,y).P_fitness(1,pp)=csrn.srn(x,y).Mse(board.time_n);
    pso.particles(x,y).P_BEST(:,pp)=pso.particles(x,y).L_ID(:,pp);
else,
   if ( pso.particles(x,y).P_fitness(1,pp)>csrn.srn(x,y).Mse(board.time_n) ),
       pso.particles(x,y).P_fitness(1,pp)=csrn.srn(x,y).Mse(board.time_n);
       pso.particles(x,y).P_BEST(:,pp)=pso.particles(x,y).L_ID(:,pp);       
   end;
end;

function [csrn,pso]=pso_update_global_best(board,csrn,params,pso,x,y,pp)

%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.particles(x,y).size=5;                  % Number of particles        
%     [row_W,clmn_W] = size( csrn.srn(x,y).W );
%     [row_V,clmn_V] = size( csrn.srn(x,y).V );
%     pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%     % Initialize parameters of the PSO algorithm for a node at (x,y)
%     % Note these matrice will be expanded as "pso.particles(x,y).size"
%     % is expanded.
%     pso.particles(x,y).P_BEST = zeros( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).G_BEST = zeros( pso.particles(x,y).dimension,1 );
%     pso.particles(x,y).P_fitness = zeros( 1,pso.particles(x,y).size );
%     pso.particles(x,y).g_fitness = 10^6;
%     pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).V_ID=rand( size(pso.particles(x,y).L_ID) );
%
%      params.ERROR_CURVE=zeros(params.epoch_max,board.max_board,board.max_board);


% Update the global best, i.e. pso.particles(x,y).G_BEST
if ( pso.particles(x,y).g_fitness > min(pso.particles(x,y).P_fitness) ),
    [ pso.particles(x,y).g_fitness,best_particle ]= min(pso.particles(x,y).P_fitness);
    pso.particles(x,y).G_BEST=pso.particles(x,y).P_BEST(:,best_particle);
end;

params.ERROR_CURVE(params.epoch,x,y)=pso.particles(x,y).g_fitness;

function [csrn,pso]=pso_update_equations(board,csrn,params,pso,x,y,pp)
% pso_update_equations          Update equations in PSO
%                               PSO (Particle Swarm Optimization)
%     pp        particle_index
%
%     pso.config.w=0.8;
%     pso.config.c1=2;
%     pso.config.c2=2;
%     pso.config.target_fitness=10^-3;
%     pso.config.l_id_max=2.0;
%     pso.config.v_id_max=100;
%     pso.particles(x,y).size=5;                  % Number of particles        
%     [row_W,clmn_W] = size( csrn.srn(x,y).W );
%     [row_V,clmn_V] = size( csrn.srn(x,y).V );
%     pso.particles(x,y).dimension=row_W.*clmn_W+row_V.*clmn_V;
%     % Initialize parameters of the PSO algorithm for a node at (x,y)
%     % Note these matrice will be expanded as "pso.particles(x,y).size"
%     % is expanded.
%     pso.particles(x,y).P_BEST = zeros( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).G_BEST = zeros( pso.particles(x,y).dimension,1 );
%     pso.particles(x,y).P_fitness = zeros( 1,pso.particles(x,y).size );
%     pso.particles(x,y).g_fitness = 10^6;
%     pso.particles(x,y).L_ID=rand( pso.particles(x,y).dimension,pso.particles(x,y).size );
%     pso.particles(x,y).V_ID=rand( size(pso.particles(x,y).L_ID) );
%
%     params.ERROR_CURVE=zeros(params.epoch_max,board.max_board,board.max_board);

% Use temporary variable names 
%    because, e.g., pso.particles(x,y).L_ID is too lengthy.
L_ID=pso.particles(x,y).L_ID;
V_ID=pso.particles(x,y).V_ID;
w=pso.config.w;
c1=pso.config.c1;
c2=pso.config.c2;
P_BEST=pso.particles(x,y).P_BEST;
G_BEST=pso.particles(x,y).G_BEST;
l_id_max=pso.config.l_id_max;
v_id_max=pso.config.v_id_max;

for pp=1:pso.particles(x,y).size,
    for dd=1:pso.particles(x,y).dimension,
        V_ID(dd,pp) = w.*V_ID(dd,pp)+ c1.*rand.*( P_BEST(dd,pp)-L_ID(dd,pp) )+ c2.*rand.*( G_BEST(dd,1)-L_ID(dd,pp) );
        if ( V_ID(dd,pp)>v_id_max ),
            V_ID(dd,pp)=v_id_max;
        elseif ( V_ID(dd,pp)<-v_id_max ),
            V_ID(dd,pp)=-v_id_max;
        end;
    end;    
end;

L_ID = L_ID + V_ID;

for pp=1:pso.particles(x,y).size,
    for dd=1:pso.particles(x,y).dimension,
        if ( L_ID(dd,pp)>l_id_max ),
            L_ID(dd,pp)=l_id_max;
        elseif ( L_ID(dd,pp)<-l_id_max ),
            L_ID(dd,pp)=-l_id_max;
        end;
    end;    
end;

