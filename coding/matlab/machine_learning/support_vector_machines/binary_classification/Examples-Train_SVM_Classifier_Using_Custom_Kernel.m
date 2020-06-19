% Support_Vector_Machines/Binary_Classification/Examples-Train_SVM_Classifier_Using_Custom_Kernel.m
% https://www.mathworks.com/help/stats/support-vector-machines-for-binary-classification.html#bsr5o1q

% This examples shows
%   (1) how to use a custom kernel function
%        e.g. the sigmoid kernel 
%   (2) adjust custom kernel function parameters.

clear all; close all;

rng(1);
n = 100;  % Number of points per quadrant

% Randomly generate data
r1 = sqrt( rand(2*n,1) );  % 200-by-1
t1 = [pi/2*rand(n,1); (pi/2*rand(n,1)+pi)];  % Random angle for Q1 and Q3
X1 = [ r1.*cos(t1) r1.*sin(t1) ];

r2 = sqrt( rand(2*n,1) );
t2 = [pi/2*rand(n,1)+pi/2; (pi/2*rand(n,1)-pi/2)];  % For Q2 and Q4
X2 = [ r2.*cos(t2) r2.*sin(t2) ];

X = [X1; X2];           % Predictors = input data
Y = ones(4*n,1);        % First half is +1
Y(2*n+1:end) = -1;    % Last half is -1

% Plot Figure 1
figure;
gscatter( X(:,1), X(:,2),Y );
title('Scatter Diagram of Simulated Data')

% Add the directory where mysigmoid.m is located.
dir_name='/home/aimldl/Dropbox/matlab/5-github/svm';
addpath(dir_name);

% Train an SVM classifer with the custom function or mysigmoid
% Mdl1 is a ClassificationSVM classifier containing the estimated parameters.
Mdl1 = fitcsvm(X,Y,'KernelFunction','mysigmoid','Standardize',true);

% Compute the scores over a grid
d = 0.02;  % Step size of the grid

% CHANGED
min_X(1) = min( X(:,1) );
max_X(1) = max( X(:,1) );
min_X(2) = min( X(:,2) );
max_X(2) = max( X(:,2) );

[x1Grid,x2Grid] = meshgrid( ...
                          min_X(1): d : max_X(1), ...
                          min_X(2): d : max_X(2) );
% CHANGED

xGrid = [ x1Grid(:), x2Grid(:) ];
[~,scores1] = predict( Mdl1, xGrid );

% Figure 2
figure;
h(1:2) = gscatter( X(:,1), X(:,2), Y,'rb','.');
hold on
h(3) = plot( X( Mdl1.IsSupportVector,1), X( Mdl1.IsSupportVector, 2), 'ko', 'MarkerSize',10 );
contour( x1Grid, x2Grid, reshape( scores1(:,2), size(x1Grid) ), [0 0], 'k');
title('Scatter Diagram with the Decision Boundary')
legend( h,{'-1','+1','Support Vectors'},'Location','Best' );
%axis([-2 2 -2 2])  % CHANGED
% axis equal  % CHANGED
hold off

% Determine misclassification rate by using 10-fold cross validation.
CVMdl1 = crossval(Mdl1);
misclass1 = kfoldLoss(CVMdl1);
disp(misclass1)  % 0.1375, 13.75% is quite high. So the performance is low. :-(

% Ensure there's mysigmoid2.m
Mdl2 = fitcsvm(X,Y,'KernelFunction','mysigmoid2','Standardize',true);
[~,scores2] = predict(Mdl2,xGrid);

% Figure 3
figure;
h(1:2) = gscatter( X(:,1), X(:,2), Y,'rb','.');
hold on
h(3) = plot( X( Mdl2.IsSupportVector,1), X( Mdl2.IsSupportVector, 2), 'ko', 'MarkerSize',10 );
contour( x1Grid, x2Grid, reshape( scores2(:,2), size(x1Grid) ), [0 0], 'k');
title('Scatter Diagram with the Decision Boundary')
legend( h,{'-1','+1','Support Vectors'},'Location','Best' );
%axis([-2 2 -2 2])  % CHANGED
% axis equal  % CHANGED
hold off

% Determine misclassification rate by using 10-fold cross validation.
CVMdl2 = crossval(Mdl2);
misclass2 = kfoldLoss(CVMdl2);
disp(misclass2)  % 0.0450, 4.5% is better!

% After the sigmoid slope adjustment, the new decision boundary
% seems to provide a better within-sample fit, and
% the cross-validation rate contracts by more than 66%.
