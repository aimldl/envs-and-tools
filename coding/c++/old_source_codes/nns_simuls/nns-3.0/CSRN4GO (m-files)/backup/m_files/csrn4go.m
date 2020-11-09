function csrn=CSRN4GO(board,csrn,params,pso)
% CSRN4GO   Cellular Simultaneous Recurrent Networks for Go
%
% CSRN is a bunch of SRNs in cellular structure. In this case,
% we assume this cellular structure matches the structure of a Go board.
% Imagine a node is located at an intersection on a 9x9 Go board.
% These nodes on the board are inter-connected just like the Go board.
% In CSRN, each node corresponds to a SRN.
% This function includes the training part.

% Iteration for the simultaneous part

% The notation may be a little bit confusing.
% A position (x,y) in a catesian coordinate corresponds to [column, row] in a matrix.
% For example, a stone at (1,2) on the board is stored in
% board.STATUS(2,1). In other words, the second row and first column in a
% matrix board.STATUS should be read in order to retrieve data at (1,2) on
% the board. Visually,
%
%    1 2  3
%  1
%  2 X 
%  3
% time_n is time n to play Go. Obviously, n is discrete time index.
% ii indicates the epochs of simulation run. "i" for iteration, but "i" is
% already taken in Matlab. So, "ii" instead of "i".

% A design issue has lots of options.
%    How to iterate, how to compute the target fitness, and so on.
%    Try out this and that.
csrn.time_n=1;
while ( (csrn.time_n<=csrn.time_n_max) ),
    disp( sprintf('\tcsrn.time_n=%d',csrn.time_n) );
    csrn=update_CSRN(board,csrn,params,pso);
    if ( csrn.config.is_display_mse==1 && mod(csrn.time_n, csrn.config.display_frequency) == 0 ),
        disp( sprintf('\tMSE') );
        csrn.stats.at(csrn.time_n).MSE
    end;
    csrn.stats.at(csrn.time_n).ave_mse=mean( mean( csrn.stats.at(csrn.time_n).MSE ) );
    csrn.time_n = csrn.time_n+1;
end;