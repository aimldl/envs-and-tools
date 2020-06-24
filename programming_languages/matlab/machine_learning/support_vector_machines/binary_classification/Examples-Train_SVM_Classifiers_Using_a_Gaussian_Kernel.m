% Support_Vector_Machines/Binary_Classification/Examples-Train_SVM_Classifiers_Using_a_Gaussian_Kernel.m
% https://www.mathworks.com/help/stats/support-vector-machines-for-binary-classification.html#bsr5o1q

clear all; close all;

rng(1);  % Fix the random seed for reproducibility

% data1
% randomely generate
r = sqrt( rand(100,1) );             % radius
t = 2*pi*rand(100,1);               % angle
data1 = [r.*cos(t), r.*sin(t)];       % points

% data2
% randomely generate
r2 = sqrt( 3*rand(100,1)+1 );     % radius
t2 = 2*pi*rand(100,1);               % angle
data2 = [r2.*cos(t), r2.*sin(t2)]; % points 

% Figure 1
% Plot data1 & data2 to visualize the data

figure;
plot( data1(:,1), data1(:,2), 'r.', 'MarkerSize',15)
hold on
plot( data2(:,1), data2(:,2), 'b.', 'MarkerSize',15)
ezpolar(@(x)1);
ezpolar(@(x)2);
% axis equal  % CHANGED
axis([-2 2 -2 2])
hold off

% Put data1 & data2 in one matrix
data3 = [data1; data2];

% The first 100 is 1; the rest of 100 is -1
theclass = ones(200,1);
theclass(1:100) = -1;

% Train the SVM Classifier
% Training with the default parameters makes a more nearly circular classification boundary
% but one that misclassifies some training data. Also, the default value of BoxConstraint is 1, and, therefore, there are more support vectors.

cl = fitcsvm( data3, theclass, 'KernelFunction', 'rbf',...
       'BoxConstraint', Inf, 'ClassNames', [-1,1]);

% fitcsvm generates a classifier that is close to a circle of radius 1.
% The difference is due to the random training data.
%
% 'KernelFunction', 'rbf' means Gaussian kernel is used.
   
% Predict scores over the grid
d = 0.02;

% CHANGED
min_data3(1) = min( data3(:,1) );
max_data3(1) = max( data3(:,1) );
min_data3(2) = min( data3(:,2) );
max_data3(2) = max( data3(:,2) );

[x1Grid,x2Grid] = meshgrid( ...
                          min_data3(1): d : max_data3(1), ...
                          min_data3(2): d : max_data3(2) );
% CHANGED

xGrid = [ x1Grid(:), x2Grid(:) ];
[~,scores] = predict( cl, xGrid );

% size(x1Grid) = size(x1Grid) = 197x194
% 197x194 = 38,218

% size(scores) = size(xGrid) = 38218x2
% size( scores(:,2)) = 38218x1
 
% Figure 2
% First, plot data with class 1 and class2.
% Secondly, plot circles with radius of 1 and 2.
% Up to this point, it's identical to Figure 1.
figure;
h(1:2) = gscatter( data3(:,1), data3(:,2), theclass,'rb','.');
hold on
ezpolar( @(x)1 );
ezpolar( @(x)2 );  % CHANGED
h(3) = plot( data3( cl.IsSupportVector,1), data3( cl.IsSupportVector, 2), 'ko' );
contour( x1Grid, x2Grid, reshape( scores(:,2), size(x1Grid) ), [0 0], 'k');
legend( h,{'-1','+1','Support Vectors'} );
axis([-2 2 -2 2])  % CHANGED
% axis equal  % CHANGED
hold off
