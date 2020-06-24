function output_matrix=ssf2nif(input_matrix)
% ssf2nif       SSF to NIF
%
% This function taks an input as SSF and converts the format to NIF.

[row,clmn]=size(input_matrix);
for x=1:clmn,
    for y=1:row,
        if ( input_matrix(y,x)>0 ),
            output_matrix(y,x)=1;
        elseif ( input_matrix(y,x)==0 ),
            output_matrix(y,x)=0;
        elseif ( input_matrix(y,x)<0),
            output_matrix(y,x)=-1; 
        end;        
    end;
end;


