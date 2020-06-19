function CSRNwHF=init_csrn(board),
% init_csrn   initialize CSRN
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
% CSRNwHF=initialize_CSRNwHF(board);
%
% structure board should be initialized earlier.
% ??? Undefined variable "board" or class "board.cfg.size".
% 
% Error in ==> initialize_CSRNwHF at 27
% CSRNwHF.cfg.struct=[board.cfg.size, board.cfg.size];    % row-by-column structure
% 
% Error in ==> main_CSRNwHF4GO at 55
% CSRNwHF=initialize_CSRNwHF();

CSRNwHF.cfg.noise_max   = 10.^-3;
CSRNwHF.cfg.N_n         = 2;                          % Number of neighbors
CSRNwHF.cfg.N_u         = (CSRNwHF.cfg.N_n+1)*2+1;    % Number of inputs to a SRN in the input layer "u"
CSRNwHF.cfg.N_h         = 5;                          % Number of hidden layer neurons
CSRNwHF.cfg.N_v         = 1;                          % Number of neurons in output layer
CSRNwHF.cfg.N_N         = [ CSRNwHF.cfg.N_u, CSRNwHF.cfg.N_h, CSRNwHF.cfg.N_v ];    % Number of neurons in layers, [layer_1, layer_2, ..., layer_n]

% Location of the self-feedback input
% Putting the fb input to the first column will be more convenient.
N_u                     = CSRNwHF.cfg.N_u;
N_h                     = CSRNwHF.cfg.N_h;
N_s                     = board.cfg.N_s;

CSRNwHF.srn.q.fb_u      = 1;
CSRNwHF.srn.U           = 0;
CSRNwHF.srn.W_u         = zeros( N_h,N_u );
CSRNwHF.srn.W_v         = zeros( 1,N_h );

% Output layer (v) output
CSRNwHF.srn.v_o         = 0;

% SRN output, typically same as the output layer output in our case.
% SRN's input requires SRN output, so randomize the initial SRN outputs.
% Check the validity to randomize the initial SRN outputs.
board_max               = board.cfg.size;
CSRNwHF.srn.Y_hat       = rand(board_max, board_max);

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
        CSRNwHF.srn.loc(x,y).SCOPE=board_dummy(y:y+2,x:x+2);
        if (CSRNwHF.srn.loc(x,y).SCOPE(2,1)~=inf),
            CSRNwHF.srn.loc(x,y).SCOPE(2,1)=1;
        end;        
        if (CSRNwHF.srn.loc(x,y).SCOPE(1,2)~=inf),
            CSRNwHF.srn.loc(x,y).SCOPE(1,2)=1;            
        end;        
        if (CSRNwHF.srn.loc(x,y).SCOPE(3,2)~=inf),
            CSRNwHF.srn.loc(x,y).SCOPE(3,2)=1;            
        end;        
        if (CSRNwHF.srn.loc(x,y).SCOPE(2,3)~=inf),
            CSRNwHF.srn.loc(x,y).SCOPE(2,3)=1;            
        end;
        CSRNwHF.srn.loc(x,y).SCOPE(2,2)=1;
    end;    
end;