function board=generate_rand_board(board),

board.STATUS=floor(3.*rand(board.max_board,board.max_board))-1;