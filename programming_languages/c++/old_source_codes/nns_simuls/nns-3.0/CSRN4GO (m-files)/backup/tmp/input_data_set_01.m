function board=input_data_set_01(board);

if ( board.cfg.size==2 ),
    board.cfg.N_B=7;    % This is equal to the total number of input data set.
    
    % Empty the boards
    STRING_SIZE_TMP = zeros( board.cfg.size,board.cfg.size );
    BOARD_STATUS_TMP = zeros( board.cfg.size,board.cfg.size );    
    for nn=1:board.cfg.N_B,
        % Store the generated test input as NN target function
        % and convert it to a regular board representation as NN input function
        board.at(nn).STRING_SIZE=STRING_SIZE_TMP;
        nn=nn+1;
    end;
    
    % Place stones manually.
    board.at(1).STRING_SIZE(1,1)=1;
    
    board.at(2).STRING_SIZE(1,1)=1;
    board.at(2).STRING_SIZE(2,2)=-1;

    board.at(3).STRING_SIZE(1,1)=2;
    board.at(3).STRING_SIZE(1,2)=2;
    board.at(3).STRING_SIZE(2,2)=-1;

    board.at(4).STRING_SIZE(1,1)=2;
    board.at(4).STRING_SIZE(1,2)=2;
    board.at(4).STRING_SIZE(2,1)=-2;
    board.at(4).STRING_SIZE(2,2)=-2;

    board.at(5).STRING_SIZE(1,1)=2;
    board.at(5).STRING_SIZE(1,2)=2;
    board.at(5).STRING_SIZE(2,1)=0;
    board.at(5).STRING_SIZE(2,2)=0;
    
    board.at(6).STRING_SIZE(1,1)=3;
    board.at(6).STRING_SIZE(1,2)=3;
    board.at(6).STRING_SIZE(2,1)=3;
    board.at(6).STRING_SIZE(2,2)=-1;

    board.at(7).STRING_SIZE(1,1)=3;
    board.at(7).STRING_SIZE(1,2)=3;
    board.at(7).STRING_SIZE(2,1)=3;
    board.at(7).STRING_SIZE(2,2)=0;
    
    for nn=1:board.cfg.N_B,    
        board.at(nn).STATUS=ssf2nif( board.at(nn).STRING_SIZE );    
        nn=nn+1;
    end;
    
end;
