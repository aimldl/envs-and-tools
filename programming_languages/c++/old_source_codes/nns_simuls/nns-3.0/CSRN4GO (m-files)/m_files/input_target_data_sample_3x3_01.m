% input_target_data_sample_3x3_01
% This is designed for testing a 3x3 board.
% This m-file is called by get_input_target_data

data.target(1).SS(1,1)=1;

data.target(2).SS(1,1)=1;
data.target(2).SS(1,3)=1;
data.target(2).SS(2,2)=-1;
data.target(2).SS(3,3)=-1;

data.target(3).SS(1,1)=2;
data.target(3).SS(1,2)=2;
data.target(3).SS(2,2)=-2;
data.target(3).SS(3,2)=-2;

data.target(4).SS(1,1)=2;
data.target(4).SS(1,2)=2;
data.target(4).SS(2,1)=-2;
data.target(4).SS(2,2)=-2;
data.target(4).SS(3,3)=1;

data.target(5).SS(1,1)=3;
data.target(5).SS(1,2)=3;
data.target(5).SS(1,3)=3;
data.target(5).SS(3,2)=-2;
data.target(5).SS(3,3)=-2;

data.target(6).SS(1,1)=3;
data.target(6).SS(1,2)=3;
data.target(6).SS(2,1)=3;
data.target(6).SS(2,2)=-3;
data.target(6).SS(3,2)=-3;
data.target(6).SS(3,3)=-3;

data.target(7).SS(1,1)=3;
data.target(7).SS(1,2)=3;
data.target(7).SS(2,1)=3;
data.target(7).SS(2,2)=-3;
data.target(7).SS(2,3)=-3;
data.target(7).SS(1,3)=-3;

