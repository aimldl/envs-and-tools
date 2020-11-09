function board=generate_test_input_files(board),

no_strings_max=10;
string_size_max=round(board.max_board/2);

for nn=1:board.no_test_input_files,
    % Randomly generate test input files
    no_ttl_strings = ceil( no_strings_max.*rand );
    STRING_SIZE_TMP = zeros( board.max_board,board.max_board );
    BOARD_STATUS_TMP = zeros( board.max_board,board.max_board );    
    % (x,y) as much as no_ttl_strings    
    location=ceil( board.max_board.*rand(2,no_ttl_strings) );
    for str=1:no_ttl_strings,
        % Starting from 1, alternate 1 (black) and -1 (white).
        string_size_target=ceil( string_size_max.*rand );
        player=-(-1).^str;      
        x_target=location(1,str);
        y_target=location(2,str);
        
        % Check if the grid at the target location is empty.
        string_size=0;
        x=x_target;
        y=y_target;
        while ( x<=board.max_board && string_size<string_size_target ),
            if ( BOARD_STATUS_TMP(y,x)==0 ),
                BOARD_STATUS_TMP(y,x)=player;
                string_size=string_size+1;
                x=x+1;
            else,
                break;
            end;
        end;

        % mark the calculated string size
        % The string size for black and white has a posivie and negative
        % value, respectively, i.e. +2 for black, -2 for white
        x=x_target;
        y=y_target;
        mark_counter=1;
        while ( mark_counter<=string_size ),
            STRING_SIZE_TMP(y,x)=player.*string_size;
            mark_counter=mark_counter+1;
            x=x+1;
        end;
    end;
    % Generate test input files randomly

    % Store the generated test input as NN target function
    % and convert it to a regular board representation as NN input function
    board.at(nn).STRING_SIZE=STRING_SIZE_TMP;
    board.at(nn).STATUS=ssf2nif( board.at(nn).STRING_SIZE );
    nn=nn+1;
end;