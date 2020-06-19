function [csrn,pso]=SRNwHF(board,csrn,params,pp,pso,x,y)
% SRN       A module for Simultaneous Recurrent Network
%
% How the SRN structure is constrcuted.
%
%    This SRN module contains a FFNN (Feed-forward Neural Networks).
%    The FFNN's output is fed back as input to the FFNN, and this constructs a
%    Recurrent Network structure.
%    This feedback is iterated a multiple number of times, which constitutes a
%    Simultaneous Recurrent Network structure.
%
% The training algorithm is incorporated into this module.
%    The reason is because the weights of the FFNN should be updated as the
%    FFNN output is iteratively fedback to its input.

% Note that input to a NN should be [-1,1];
% -no_hidden_neurons<=y_hat<=no_hidden_neurons because -1<=tansig(.)<=1
%             N_h
% and y_hat = sum tansig(.)
%             n=1   
%y_hat= W_v*H_o;
% y_target is an integer STRING_SIZE ranges from -string_size_max to string_size_max.
% Error is the difference between the target string size and the
% estimated string size. Ideally, the error should be an integer.
% However, it's less likely to happen, so the error should be forced to
% become an integer. I don't know which one is the best among
% ceil, floor, and round, but I believe the first two may work just fine
% as long as either of them is used consistently. 
% *** Double-check if this definition of error is fine.    

% Variable mapping.
%U=csrn.srn(x,y).Input2nn;
%ttl_no_input=csrn.srn(x,y).input2nn_lengh;
ttl_no_input=csrn.srn(x,y).input_length;
U=csrn.srn(x,y).Input;
% y_target is an integer STRING_SIZE ranges from -string_size_max to string_size_max.
y_target=board.at(board.time_n).STRING_SIZE(x,y);

% Use symmetry
x=1;y=1;
W_u=csrn.srn(x,y).W_u;
% In order to use PSO, a multiple number of PSO is necessary.
% The siblings try out several different weights and the best one will be
% saved as the hidden layer weights for the parent.

% Initial values
W_h=csrn.srn(x,y).W_h;
W_v=csrn.srn(x,y).W_v';

w=pso.cfg.associate.w;
c1=pso.cfg.associate.c1;
c2=pso.cfg.associate.c2;
l_id_max=pso.cfg.associate.l_id_max;
v_id_max=pso.cfg.associate.v_id_max;
dimension_a=pso.cfg.associate.d;
size_a=pso.cfg.associate.size;

% If H_o is reused for different siblings, H_o may grow monotonically.
% To avoid this problem, one H_o per sibling

% Initial values
t_max=pso.associate.time_m_max;
fitness_t=pso.cfg.associate.target_fitness;
fitness_g=pso.cfg.associate.g_fitness;

L_ID=pso.a(pp).L_ID;
V_ID=pso.a(pp).V_ID;
P_BEST=pso.a(pp).P_BEST;
G_BEST=pso.a(pp).G_BEST;
H_o=pso.a(pp).H_o;

% P_fitness should be emptied every time because
% the outer-loop PSO updates 
P_fitness=zeros( 1,size_a );

% Compute the NN output
% Note that input to a NN should be [-1,1];
% Therefore, tansig should be used because tansig(x) in [-1,1].
% logsig(x) is between [0,1]
D=tansig( W_u*U );
tmp_D=[D';ones(size(D'))];
% The recurrency in the hidden layer:
% All the hidden layer outputs are summed and input to the node.

% Do I need to iterate in the hidden layer?

% For Hidden_neuron_out<1, Hidden_neuron_in<=5. 
% e.g. tansig(5)=0.9999
% tansig(2)=0.9640
% tansig(1)=0.7616

% t_m is the time index for the inner loop.
t_m=1;

while ( (t_m<=t_max) && (fitness_g>=fitness_t) ),
    for aa=1:size_a,
% Hidden layer
        % New H_o and W_h c are applied at each iteration.
        H_i=[];
        for ii=1:csrn.config.No_neurons(2),
            H_i=[H_i,H_o(:,aa)];
        end;
        H_i=[H_i;tmp_D];
        H_o(:,aa)=diag( W_h*H_i );
% Output layer
        % Activation function for the output layer is floor.
        y_hat= floor( W_v*H_o(:,aa) );
% Error calculation
        error_y= abs( y_target-y_hat );
        
% Update local best
        if ( (P_fitness(1,aa)==0) && (t_m==1) ),
            P_fitness(1,aa)=error_y;
            P_BEST(:,aa)=L_ID(:,aa);
        else,
           if ( P_fitness(1,aa)>error_y ),
               P_fitness(1,aa)=error_y;
               P_BEST(:,aa)=L_ID(:,aa);       
           end;
        end;
    end;

% Update global best
    if ( fitness_g > min(P_fitness) ),
        [ fitness_g,best_particle ]= min(P_fitness);
        G_BEST=P_BEST(:,best_particle);
    end;
%    pso.node(x,y).siblings.error.At(t_m) = fitness_g;

    % Update equations    

    for aa=1:size_a,
        for dd=1:dimension_a,
            V_ID(dd,aa) = w.*V_ID(dd,aa)+ c1.*rand.*( P_BEST(dd,aa)-L_ID(dd,aa) )+ c2.*rand.*( G_BEST(dd,1)-L_ID(dd,aa) );
            if ( V_ID(dd,aa)>v_id_max ),
                V_ID(dd,aa)=v_id_max;
            elseif ( V_ID(dd,aa)<-v_id_max ),
                V_ID(dd,aa)=-v_id_max;
            end;
        end;    
    end;
    L_ID = L_ID + V_ID;
    for aa=1:size_a,
        for dd=1:dimension_a,
            if ( L_ID(dd,aa)>l_id_max ),
                L_ID(dd,aa)=l_id_max;
            elseif ( L_ID(dd,aa)<-l_id_max ),
                L_ID(dd,aa)=-l_id_max;
            end;
        end;
    end;
    t_m = t_m+1;
end;

% Store the values
% Actually, all we need from associates are the hidden layer weights.
% In other words, the global best among all the associates.
% But save the rest of variables without a particular reason.

% fitness_g is the smallest error_y.
% fitness_g <== pso.a(pp).P_fitness <== error_y
% Because pso.a(pp).P_fitness(1,aa)=error_y; and 
% [ fitness_g,best_particle ]= min(pso.a(pp).P_fitness);
pso.associate.g_fitness=fitness_g;
%pso.a(pp).H_o=H_o;
% Store the updated location and velocity back to structure pso
% Last updated location and velocity
% This doesn't need to be kept because particle's new location has
% nothing to do with this old location and velocity. 
% This old location and velocity will be used as as the initial point.
% This can rather be randomized, too.
pso.a(pp).L_ID=L_ID;
pso.a(pp).V_ID=V_ID;

pso.a(pp).P_BEST=P_BEST;
pso.a(pp).G_BEST=G_BEST;
pso.a(pp).H_o=H_o;
