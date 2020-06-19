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

csrn.config.is_display_mse=0;
csrn.config.display_frequency=10;

% Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
%csrn.config.No_neurons=[3,1];
csrn.config.No_neurons=[2.*board.string_size_max,1];
csrn.config.bias=1;
csrn.config.noise_max=10.^-3;

% Epoch, time n, or iteration counter for CSRN
csrn.time_n=1;
csrn.time_n_max=10;

% MSE of this CSRN
csrn.stats.at(1).MSE=inf;
% Average MSE=average(MSE)
csrn.stats.at(1).ave_mse=inf;

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
        csrn.srn(x,y).input_lengh=(csrn.srn(x,y).no_neighbors+1)*2+1;
        csrn.srn(x,y).fb_input_location=(csrn.srn(x,y).no_neighbors+1)+1;        
        csrn.srn(x,y).Input=0;
        csrn.srn(x,y).W=zeros( csrn.config.No_neurons(1),csrn.srn(x,y).input_lengh );
        csrn.srn(x,y).V=zeros( csrn.config.No_neurons(2),csrn.config.No_neurons(1) );
        % Ranging from -1 to 1
        csrn.srn(x,y).H_neuron_out.At=rand(1,csrn.config.No_neurons(1));
        csrn.srn(x,y).output.At=inf;
        csrn.srn(x,y).target=inf;        
        csrn.srn(x,y).error_y.At=inf;
        csrn.srn(x,y).mse.At=inf;
        csrn.srn(x,y).mse_tmp.At=inf;        
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