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

% SRN output, typically same as the output layer output in our case.
% SRN's input requires SRN output, so randomize the initial SRN outputs.
% Check the validity to randomize the initial SRN outputs.
board_max            = board.cfg.size;
csrn.cfg.noise_max   = 10.^-3;
N_s                  = board.cfg.N_s;

csrn.cfg.iter_max    = iter_max;                          % Iteration within SRN

% N_n is the number of neighbors
for x=1:board_max,
    for y=1:board_max,
        if ( (x==1 && y==1)||(x==1 && y==board_max) || (x==board_max && y==1) ||(x==board_max && y==board_max) ),
            csrn.cell.loc(x,y).N_n=2;
        elseif ( x==1 || y==1 || x==board_max || y==board_max),
            csrn.cell.loc(x,y).N_n=3;
        else,
            csrn.cell.loc(x,y).N_n=4;
        end;
        % Later, U should be a vector.
        csrn.cell.loc(x,y).U=0;
    end;
end;

% To use the symmetry, there are only three cells.
% Cell_1 is one with two neighbors, cell_2 with three, and cell_3 with
% four. The index of a cell is (N_n-1)
csrn.cell.Y_hat      = rand(board_max, board_max);

if ( board_max==2 ),
    csrn.cell.N_n_max=2;
else,
    csrn.cell.N_n_max=4;
end;

for N_n=2:csrn.cell.N_n_max,
    % Location of the self-feedback input is omittted.
    % Putting the fb input to the first column will be more convenient.
    N_u                 = (N_n+1)*2+1;
    N_h                 = 5;
    N_v                 = 1;

    csrn.cell.id(N_n-1).N_u  = N_u;                          % Number of inputs to the input layer "u"
    csrn.cell.id(N_n-1).N_h  = N_h;                          % Number of hidden layer neurons
    csrn.cell.id(N_n-1).N_v  = N_v;                          % Number of neurons in output layer
    csrn.cell.id(N_n-1).N_N  = [ N_u,N_h,N_v ];              % Number of neurons in layers, [layer_1, layer_2, ..., layer_n]    

    % The following quantities are used when PSOwHF merges the associates'
    % global best to particle's local best.
    % Note 
    % csrn.cell.id(N_n-1).w_u_start=1
    csrn.cell.id(N_n-1).w_u_end=N_h.*N_u;
    % csrn.cell.id(N_n-1).w_h_start=csrn.cell.id(N_n-1).w_u_end+1;        
    csrn.cell.id(N_n-1).w_h_end=csrn.cell.id(N_n-1).w_u_end+N_h.*(N_h+2);
    % csrn.cell.id(N_n-1).w_v_start=csrn.cell.id(N_n-1).w_h_end+1;
    % csrn.cell.id(N_n-1).w_v_end=the size of the vector;
    
    csrn.cell.id(N_n-1).W_u  = zeros( N_h,N_u );
%    csrn.cell.id(N_n-1).W_h  = zeros( N_h,N_u );
    csrn.cell.id(N_n-1).W_v  = zeros( 1,N_h );
    csrn.cell.id(N_n-1).H_o  = rand(N_h,1);      % Hidden layer (h)output
    csrn.cell.id(N_n-1).v_o  = 0;                % Output layer (v) output
end;

%csrn.cell.q.fb_u      = 1;

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