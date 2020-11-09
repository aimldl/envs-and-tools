function CSRNwHF=initialize_CSRNwHF(board),
% initialize_CSRNwHF   initialize a structure CSRNwHF 
%
% CSRNwHF (Cellular Simultaneous Recurrent Networks) with hidden layer
% feedback
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
% ??? Undefined variable "board" or class "board.max_board".
% 
% Error in ==> initialize_CSRNwHF at 27
% CSRNwHF.config.struct=[board.max_board, board.max_board];    % row-by-column structure
% 
% Error in ==> main_CSRNwHF4GO at 55
% CSRNwHF=initialize_CSRNwHF();

CSRNwHF.config.is_display_mse=0;
CSRNwHF.config.display_frequency=10;
CSRNwHF.config.bias=1;
CSRNwHF.config.noise_max=10.^-3;

% Epoch, time n, or iteration counter for CSRNwHF
CSRNwHF.time_n=1;
CSRNwHF.time_n_max=10;

% Initialize the weight matrix
for x=1:board.max_board,
    for y=1:board.max_board,
        if ( (x==1 && y==1)||(x==1 && y==board.max_board) || (x==board.max_board && y==1) ||(x==board.max_board && y==board.max_board) ),
            CSRNwHF.srn(x,y).no_neighbors=2;
        elseif ( x==1 || y==1 || x==board.max_board || y==board.max_board),
            CSRNwHF.srn(x,y).no_neighbors=3;
        else,
            CSRNwHF.srn(x,y).no_neighbors=4;
        end;
    end;
end;

% Initialize the weight matrix
for x=1:board.max_board,
    for y=1:board.max_board,
        % Initialize the weights
        % To randomize the weights, the training algorithm, e.g. PSO,
        % should map the randomized initial values to NN weights!
        %
        % CSRNwHF.config.No_neurons(1): Number of neurons at layer 1
        % CSRNwHF.config.No_neurons(2): Number of neurons at layer 2
        %
        % Later, CSRNwHF.srn(x,y).input_lengh, CSRNwHF.srn(x,y).Input, and
        % CSRNwHF.srn(x,y).Input2nn will be computed.
        %    CSRNwHF.srn(x,y).input_lengh=length(CSRNwHF.srn(x,y).Input);
        %    CSRNwHF.srn(x,y).Input2nn=[CSRNwHF.srn(x,y).Input,1];
        % The relationship between these variables & "CSRNwHF.srn(x,y).no_neighbors+1"
        % is as follows.
        %    CSRNwHF.srn(x,y).input_lengh=(CSRNwHF.srn(x,y).no_neighbors+1)*2;
        %    length(CSRNwHF.srn(x,y).Input2nn)
        %   =CSRNwHF.srn(x,y).input_lengh+1
        %   =(CSRNwHF.srn(x,y).no_neighbors+1)*2+1
        
        % Number of neurons in layers, [layer_1, layer_2, ..., layer_n]
       
        % Number of input neurons
        CSRNwHF.srn(x,y).input_length=(CSRNwHF.srn(x,y).no_neighbors+1)*2+1;        
        N_u=CSRNwHF.srn(x,y).input_length;
        % Number of hidden layer neurons
        N_h=5;
        % Number of hidden neuron elements or inputs
        N_e=N_h+2;
        % Number of output neurons
        N_v=1;
%        CSRNwHF.config.No_neurons=[2.*board.string_size_max,1];        
        CSRNwHF.config.No_neurons=[ N_u, N_h, N_v ];
        
        % Putting the fb input to the first column will be more convenient.
%        CSRNwHF.srn(x,y).fb_input_location=(CSRNwHF.srn(x,y).no_neighbors+1)+1;
        CSRNwHF.srn(x,y).fb_input_location=1;
        CSRNwHF.srn(x,y).Input=0;
%        CSRNwHF.srn(x,y).W=zeros( CSRNwHF.config.No_neurons(1),CSRNwHF.srn(x,y).input_lengh );
%        CSRNwHF.srn(x,y).V=zeros( CSRNwHF.config.No_neurons(2),CSRNwHF.config.No_neurons(1) );
        CSRNwHF.srn(x,y).W_u=zeros( N_h,N_u );
        CSRNwHF.srn(x,y).W_h=zeros( N_h,N_e  );
        CSRNwHF.srn(x,y).W_v=zeros( 1,N_h );

        % The following quantities are used when PSOwHF merges the associates'
        % global best to particle's local best.
        % Note 
        % CSRNwHF.srn(x,y).w_u_start=1
        CSRNwHF.srn(x,y).w_u_end=N_h.*N_u;
        % CSRNwHF.srn(x,y).w_h_start=CSRNwHF.srn(x,y).w_u_end+1;        
        CSRNwHF.srn(x,y).w_h_end=CSRNwHF.srn(x,y).w_u_end+N_h.*(N_h+2);
        % CSRNwHF.srn(x,y).w_v_start=CSRNwHF.srn(x,y).w_h_end+1;
        % CSRNwHF.srn(x,y).w_v_end=the size of the vector;
        
        % Hidden layer output
        CSRNwHF.srn(x,y).H_output=rand(N_h,1);
        % Output layer (v) output
        CSRNwHF.srn(x,y).v_output=0;
        % Ranging from -1 to 1
        CSRNwHF.srn(x,y).output.At=inf;
        CSRNwHF.srn(x,y).target=inf;        
        CSRNwHF.srn(x,y).error_y.Time=inf;
        CSRNwHF.srn(x,y).mse.At=inf;
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
        CSRNwHF.srn(x,y).scope.IS_SCOPE=board_dummy(y:y+2,x:x+2);
        % Mark the scope
        %         (1,2)
        % (2,1)   (2,2)   (2,3)
        %         (3,2)
        if (CSRNwHF.srn(x,y).scope.IS_SCOPE(2,1)~=inf),
            CSRNwHF.srn(x,y).scope.IS_SCOPE(2,1)=1;
        end;        
        if (CSRNwHF.srn(x,y).scope.IS_SCOPE(1,2)~=inf),
            CSRNwHF.srn(x,y).scope.IS_SCOPE(1,2)=1;            
        end;        
        if (CSRNwHF.srn(x,y).scope.IS_SCOPE(3,2)~=inf),
            CSRNwHF.srn(x,y).scope.IS_SCOPE(3,2)=1;            
        end;        
        if (CSRNwHF.srn(x,y).scope.IS_SCOPE(2,3)~=inf),
            CSRNwHF.srn(x,y).scope.IS_SCOPE(2,3)=1;            
        end;
        CSRNwHF.srn(x,y).scope.IS_SCOPE(2,2)=1;
    end;    
end;