function e_t=update_total_error(data,bb,e_t);

% update_total_error        Update the total error
%
% This function calculates the error between the target and the estimated
% string size of the board. Note both quantities are in a square matrix.
% This is a matrix version of an error calculation.
%   error_y= abs( y_target-y_hat );
%
% The total number of error is the difference of all locations on the
% board.

E_y=abs( data.target(bb).SS - data.estimate(bb).SS );
e_t=e_t+sum( sum(E_y) );