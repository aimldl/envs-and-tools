function csrn=init_csrn(board,iter_max);
% init_csrn         initialize a structure csrn 
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

csrn.cfg.noise_max   = 10.^-3;
csrn.cfg.N_n         = 2;                          % Number of neighbors
csrn.cfg.N_u         = (csrn.cfg.N_n+1)*2+1;    % Number of inputs to a SRN in the input layer "u"
csrn.cfg.N_h         = 5;                          % Number of hidden layer neurons
csrn.cfg.N_v         = 1;                          % Number of neurons in output layer
csrn.cfg.N_N         = [ csrn.cfg.N_u, csrn.cfg.N_h, csrn.cfg.N_v ];    % Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
csrn.cfg.iter_max    = iter_max;                          % Iteration within SRN

% Location of the self-feedback input
% Putting the fb input to the first column will be more convenient.
N_u                 = csrn.cfg.N_u;
N_h                 = csrn.cfg.N_h;
N_s                 = board.cfg.N_s;

csrn.cell.q.fb_u      = 1;
csrn.cell.U           = 0;
csrn.cell.W_u         = zeros( N_h,N_u );
csrn.cell.W_v         = zeros( 1,N_h );

% Output layer (v) output
csrn.cell.v_o         = 0;

% SRN output, typically same as the output layer output in our case.
% SRN's input requires SRN output, so randomize the initial SRN outputs.
% Check the validity to randomize the initial SRN outputs.
board_max            = board.cfg.size;
csrn.cell.Y_hat      = rand(board_max, board_max);

% Initialize the scope of SRNs
scope_max               = board.cfg.size+2;
board_dummy             = zeros(scope_max,scope_max);
for x=1:scope_max,
    for y=1:scope_max,
        if ( x==1 || y==1 || x==scope_max || y==scope_max ),
            % Mark the out-of-boundary position to infinity
            board_dummy(x,y)=inf;
        end;
    end;
end;

% x and y correspond to column and row, respectively.
% Note it's not row and column.

% A src at location (x,y) has a scope.
% This scope is necessary to identify the neighbors at each location.
% Mark the scope for a center at (2,2)
%         (1,2)
% (2,1)   (2,2)   (2,3)
%         (3,2)

for x=1:board_max,
    % Mark the boundary on the board
    for y=1:board_max,
        csrn.cell.loc(x,y).SCOPE=board_dummy(y:y+2,x:x+2);
        if (csrn.cell.loc(x,y).SCOPE(2,1)~=inf),
            csrn.cell.loc(x,y).SCOPE(2,1)=1;
        end;        
        if (csrn.cell.loc(x,y).SCOPE(1,2)~=inf),
            csrn.cell.loc(x,y).SCOPE(1,2)=1;            
        end;        
        if (csrn.cell.loc(x,y).SCOPE(3,2)~=inf),
            csrn.cell.loc(x,y).SCOPE(3,2)=1;            
        end;        
        if (csrn.cell.loc(x,y).SCOPE(2,3)~=inf),
            csrn.cell.loc(x,y).SCOPE(2,3)=1;            
        end;
        csrn.cell.loc(x,y).SCOPE(2,2)=1;
    end;    
end;