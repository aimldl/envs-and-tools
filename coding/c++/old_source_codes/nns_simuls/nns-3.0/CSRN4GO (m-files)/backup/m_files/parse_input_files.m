function board=parse_input_files(board)

nn=1;

load 276801-0.ssf;
load 276756-0.ssf;

board.Time(nn).STRING_SIZE=X276801_0;
board.Time(nn).STATUS=ssf2nif( board.Time(nn).STRING_SIZE );
nn=nn+1;

board.Time(nn).STRING_SIZE=X276756_0;
board.Time(nn).STATUS=ssf2nif( board.Time(nn).STRING_SIZE );
nn=nn+1;