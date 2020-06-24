% test recurrence in hidden neurons
% Apr. 23, 2008 (Wed)

board.max_board=3;
csrn.config.No_neurons=[2.*board.string_size_max,1];

x=1; y=1; csrn.time_n=1;
% Ranging from -1 to 1
csrn.srn(x,y).H_neuron_out.At=rand(1,csrn.config.No_neurons(1));

% Say the input is zero
Input_layer_out=zeros( size(Hidden_neuron_out) );
Hidden_neuron_out=csrn.srn(x,y).H_neuron_out.At(csrn.time_n,:);
Hidden_neuron_in=Input_layer_out+sum ( Hidden_neuron_out );
Hidden_neuron_out=tansig( Hidden_neuron_in );

for ii=1:10,
    Hidden_neuron_in=Input_layer_out+sum ( Hidden_neuron_out );
    Hidden_neuron_out=tansig( Hidden_neuron_in )
end;
