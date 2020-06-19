function board = place_a_stone_at(location, board)
% location=[x,y]

if ( location(1)<1 || location(1)>board.max_board || location(2)<1 || location(2)>board.max_board ),
    error('Invalid range of x,y');
end;

% 1 for black; -1 for white
% future: a function to remove stones needs to be implemented.

board.player=-(-1).^mod(board.time_n,2);
board.status(location(1),location(2)) = board.player;

