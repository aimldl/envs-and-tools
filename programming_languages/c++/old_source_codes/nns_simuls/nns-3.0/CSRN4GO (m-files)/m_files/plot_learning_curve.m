function plot_learning_curve(rec,simul,brd_size,varargin);

% plot_learning_curve       Plot the learning curve

if ( nargin==5 ),
    output_dir_name  = varargin{1};
    output_file_name = varargin{2};
    output_file = sprintf( '%s/%s',output_dir_name,output_file_name);
end;

nn_max=simul.cfg.nn_max;
scaler=simul.cfg.plot.y_scaler;
nnc_type=simul.cfg.nnc_type;

x_min=1;
x_max=nn_max;
y_min=0;
y_max=scaler.*ceil( max(rec.e_t)/scaler );

% Pass a figure handle 'h' as a variable to the function form of print
hdl_fig=figure;
plot( [1:nn_max],rec.e_t );
grid on;
axis([x_min x_max y_min y_max]);

if ( nargin==5 ),
    title( sprintf('Learning curve:%dx%d,%s',brd_size,brd_size,output_file_name) );
else,
    title( sprintf('Learning curve: %s, %dx%d',nnc_type,brd_size,brd_size) );
end;
ylabel('Total errors');
xlabel('epochs (n)');

% Save the figure as a file.
print(hdl_fig, '-djpeg', output_file);

% print(hdl_fig, '-dmeta', output_file);
% The option -dmeta is only for Windows.
% You will see the following error message.
% ??? Error using ==> graphics/private/inputcheck>LocalCheckHandles at 307
% Error using ==> graphics/private/inputcheck>LocalCheckHandles at 191
% Handle input argument contains non-handle value(s).
% 
% Error in ==> plot_learning_curve at 29
% print(hdl_fig, '-dmeta', output_file);