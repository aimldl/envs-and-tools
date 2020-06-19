% Signal Classification Using Wavelet-Based Features and Support Vector Machines
% https://www.mathworks.com/help/wavelet/examples/ecg-classification-using-wavelet-features.html
%
% The problem of signal classification is simplified by transforming the raw ECG signals into 
% a much smaller set of features that serve in aggregate to differentiate different classes. 
%
% You must have
%   Wavelet Toolbox™,
%   Signal Processing Toolbox™, and
%   Statistics and Machine Learning Toolbox™
% to run this example.
%
% The data used in this example are
%   publicly available from PhysioNet. https://physionet.org/

% Download data
%   $ git clone https://github.com/mathworks/physionet_ECG_data.git

clear all; close all;

% Load Files
my_dir = '/home/aimldl/Dropbox/matlab/2-tutorials/7-Signal_Classification_Using_Wavelet-Based_Features_and_Support_Vector_Machines/physionet_ECG_data'
load( fullfile( my_dir, 'ECGData.mat') );

% Create Training and Test data
percent_train = 70;
[trainData, testData, trainLabels, testLabels] = helperRandomSplit( percent_train, ECGData );

% Overall class percentages in the data set
Ctrain = countcats( categorical( trainLabels ) ) ./ numel( trainLabels) .* 100;
Ctest = countcats( categorical(testLabels) ) ./ numel( testLabels ) .* 100;

% Plot Samples
helperPlotRandomRecords( ECGData, 14 );

% Feature Extraction
timeWindow = 8192;
ARorder = 4;
MODWPTlevel = 4;
[trainFeatures, testFeatures, featureindices ] = ...
    myhelperExtractFeatures( trainData, testData, timeWindow, ARorder, MODWPTlevel );

% Problem:
%   'helperExtractFeatures' is used in Signal Classification Using Wavelet-Based Features and Support Vector Machines.
%   Permission denied
% Hint:
%   helperExtractFeatures is given at the bottom of the tutorial page.
% Solution:
%   Copy the content of the function, change the function name to myhelperExtractFeatures (by adding my),
%   and save it as an m file myhelperExtractFeatures.m in the same directory this m file is located.

allFeatures = [ trainFeatures ; testFeatures ] ;
allLabels = [ trainLabels; testLabels ];

% Plot the feature corresponding to the 169 column of all the rows (ECG data)
% and see the variance on this feature.
figure
boxplot( allFeatures(:, featureindices.HRfeatures(1) ), allLabels, 'notch','on');
ylabel( 'Holder Exponent Range')
title( 'Range of Singularity Spectrum by Group (First Time Window)' )
grid on

b = allFeatures(:, 169 );  % featureindices.HRfeatures(1)
size(b);
%  163     1
min(b);
%  0.2851
max(b);
%  1.2433

[p, anovatab, st] = anova1( allFeatures(:,featureindices.HRfeatures(1) ), allLabels );
c = multcompare( st, 'display', 'off' );
%  1.0000    2.0000    0.0196    0.1149    0.2102    0.0131
%  1.0000    3.0000   -0.1589   -0.0687    0.0215    0.1745
%  2.0000    3.0000   -0.2967   -0.1836   -0.0706    0.0004

boxplot( allFeatures(:,featureindices.WVARfeatures( end -1)), allLabels, 'notch', 'on' )
ylabel( 'Wavelet Variance' )
title( 'Wavelet Variance by Group' )
grid on

% Signal Classification
features = allFeatures;
rng(1)
template = templateSVM( ...
    'KernelFunction', 'polynomial',...
    'PolynomialOrder',2,...
    'kernelScale','auto',...
    'BoxConstraint',1,...
    'Standardize',true);
model = fitcecoc(...
    features,...
    [trainLabels;testLabels],...
    'Learners',template,...
    'Coding','onevsone',...
    'ClassNames',{'ARR','CHF','NSR'} );
kfoldmodel = crossval( model, 'KFold',5);
loss = kfoldLoss( kfoldmodel ) * 100

classLabels = kfoldPredict( kfoldmodel );
[confmatCV,grouporder] = confusionmat( [trainLabels;testLabels],classLabels);

% confmatCV =
%            ARR  CHF  NSR
%   ARR    92     4     0
%   CHF   11    20     0
%   NSR    4     0    32

CVTable = myhelperPrecisionRecall( confmatCV );

% Problem:
%   'helperPrecisionRecall' is used in Signal Classification Using Wavelet-Based Features and Support Vector Machines.
% Hint:
%   helperPrecisionRecall is given at the bottom of the tutorial page.
% Solution:
%   Copy the content of the function, change the function name to myhelperPrecisionRecall (by adding my),
%   and save it as an m file myhelperPrecisionRecall.m in the same directory this m file is located.

disp( CVTable )
%            Precision    Recall    F1_Score
%            _________    ______    ________
% 
%     ARR     85.981      95.833      90.64 
%     CHF     83.333      64.516     72.727 
%     NSR        100      88.889     94.118 

% How, use the training data only and make predictions on the test data.
model = fitcecoc(...
    trainFeatures,...
    trainLabels,...
    'Learners',template,...
    'Coding','onevsone',...
    'ClassNames',{'ARR','CHF','NSR'} );
predLabels = predict( model, testFeatures );
% Instead of % classLabels = kfoldPredict( kfoldmodel );

correctPredictions = strcmp( predLabels, testLabels );
testAccuracy = sum( correctPredictions ) / length( testLabels ) * 100
% testAccuracy = 12.2449  % 0.1224 = 6/49  % Too low! unlike the tutorial.
[confmatTest, grouporder ] = confusionmat( testLabels,predLabels );
% Instead of % [confmatCV,grouporder] = confusionmat( [trainLabels;testLabels],classLabels);

% confmatTest =
%      6     0     7
%      1     0    35
%      0     0     0
% sum( sum( confmatTest ) )= 49;
% diag( confmatTest ) =
%      6
%      0
%      0
% sum( diag( confmatTest ) ) =
%      6

testTable = myhelperPrecisionRecall( confmatTest );
disp( testTable )
% testTable = 
%            Precision    Recall    F1_Score
%            _________    ______    ________
% 
%     ARR     85.714      46.154       60   
%     CHF        NaN           0      NaN   
%     NSR          0         NaN      NaN  
    