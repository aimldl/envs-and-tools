function nns=init_cmlp3(board);
% init_cmlp     initialize CMLP
%               CMLP stands for Cellular MLP as opposed to CSRN.
%               nns stands for Neural Networks System.
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
%   nns (Neural Networks System)
%       .cell   (a cell=a MLP for CMLP)
%

% SRN output, typically same as the output layer output in our case.
% SRN's input requires SRN output, so randomize the initial SRN outputs.
% Check the validity to randomize the initial SRN outputs.
board_max           = board.cfg.size;

nns.cfg.noise_max   = 10.^-3;

N_s                 = board.cfg.N_s;

% N_n is the number of neighbors
for x=1:board_max,
    for y=1:board_max,
        if ( (x==1 && y==1)||(x==1 && y==board_max) || (x==board_max && y==1) ||(x==board_max && y==board_max) ),
            nns.cell.loc(x,y).N_n=2;
        elseif ( x==1 || y==1 || x==board_max || y==board_max),
            nns.cell.loc(x,y).N_n=3;
        else,
            nns.cell.loc(x,y).N_n=4;
        end;
        % Later, U should be a vector.
        nns.cell.loc(x,y).U=0;
    end;
end;

% To use the symmetry, there are only three cells.
% Cell_1 is one with two neighbors, cell_2 with three, and cell_3 with
% four. The index of a cell is (N_n-1)
nns.cell.Y_hat= rand(board_max, board_max);
nns.cell.N_n_max=4;
%nns.cell.e_t=inf.*ones(1,N_n);
for N_n=2:nns.cell.N_n_max,
    % Location of the self-feedback input is omittted.
    % Putting the fb input to the first column will be more convenient.
    N_u                 = (N_n+1)*2+1;
    N_h                 = 5;
    N_v                 = 1;

    nns.cell.id(N_n-1).N_u  = N_u;                          % Number of inputs to the input layer "u"
    nns.cell.id(N_n-1).N_h  = N_h;                          % Number of hidden layer neurons
    nns.cell.id(N_n-1).N_v  = N_v;                          % Number of neurons in output layer
    nns.cell.id(N_n-1).N_N  = [ N_u,N_h,N_v ];              % Number of neurons in layers, [layer_1, layer_2, ..., layer_n]    

    % The following quantities are used when PSOwHF merges the associates'
    % global best to particle's local best.
    % Note 
    % nns.cell.id(N_n-1).w_u_start=1
    nns.cell.id(N_n-1).w_u_end=N_h.*N_u;
    % nns.cell.id(N_n-1).w_h_start=nns.cell.id(N_n-1).w_u_end+1;        
    nns.cell.id(N_n-1).w_h_end=nns.cell.id(N_n-1).w_u_end+N_h.*(N_h+2);
    % nns.cell.id(N_n-1).w_v_start=nns.cell.id(N_n-1).w_h_end+1;
    % nns.cell.id(N_n-1).w_v_end=the size of the vector;
    
    nns.cell.id(N_n-1).W_u  = zeros( N_h,N_u );
%    nns.cell.id(N_n-1).W_h  = zeros( N_h,N_u );
    nns.cell.id(N_n-1).W_v  = zeros( 1,N_h );
    nns.cell.id(N_n-1).H_o  = rand(N_h,1);      % Hidden layer (h)output
    nns.cell.id(N_n-1).v_o  = 0;                % Output layer (v) output
end;

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
        nns.cell.loc(x,y).SCOPE=board_dummy(y:y+2,x:x+2);
        if (nns.cell.loc(x,y).SCOPE(2,1)~=inf),
            nns.cell.loc(x,y).SCOPE(2,1)=1;
        end;        
        if (nns.cell.loc(x,y).SCOPE(1,2)~=inf),
            nns.cell.loc(x,y).SCOPE(1,2)=1;            
        end;        
        if (nns.cell.loc(x,y).SCOPE(3,2)~=inf),
            nns.cell.loc(x,y).SCOPE(3,2)=1;            
        end;        
        if (nns.cell.loc(x,y).SCOPE(2,3)~=inf),
            nns.cell.loc(x,y).SCOPE(2,3)=1;            
        end;
        nns.cell.loc(x,y).SCOPE(2,2)=1;
    end;    
end;