function board=init_board(board_size),
% A function to initialize structure board
%
% Initialize the current board representation
% EMPTY: 0, BLACK: 1, WHITE: -1
% player: black 1, white -1

board.cfg.size=board_size;
board.cfg.N_s=board.cfg.size.*board.cfg.size;       % Number of stones on a board
board.cfg.N_b=0;                                    % Number of boards, i.e. a snapshot of board status over time

% The largest string is when all the grids on the board is filled with
% one stone. That is, 81 for 9x9 board. 
% However, this is never gonna happen in practice.
% So, let's pick an arbitrarily large number. 
% Say 3xboard.max_board.
board.cfg.N_G_max = 2*board.cfg.size;               % The max number of stones in a group