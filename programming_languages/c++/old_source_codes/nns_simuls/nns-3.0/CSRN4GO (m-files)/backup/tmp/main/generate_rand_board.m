function board=generate_rand_board(board),

board.player=-(-1).^mod(board.time_n,2);
board.at(1).STATUS=floor(3.*rand(board.max_board,board.max_board))-1;