% process_dataset_manually.m

% Source: Speaker Identification Using Pitch and MFCC
%   https://www.mathworks.com/help/audio/examples/speaker-identification-using-pitch-and-mfcc.html

% Problem:
%   The following lines fail to work!
%     dataDir = HelperAN4Download;  % Path to data directory
%       ads = audioDatastore( dataDir, ...
%                                         'IncludeSubfolders', true,...
%                                         'FileExtensions', '.flac',...
%                                         'LabelSource','foldernames')
% Error message:
%   Undefined function or variable 'HelperAN4Download'.
%   Undefined function or variable 'dataDir'.
dir_root = '/home/aimldl/Dropbox/matlab/2-tutorials/8_speaker_identification_using_pitch_and_mfcc';
cd( dir_root );

detect_pitch_and_plot_the_pitch_contour;

% Alternatively, this works!
load HelperAN4TrainingFeatures.mat

% This .mat load 'features', 'm', and 's'.
%   'features' is a 17576 x 16 matrix with the following columns.
%       1             2        3             4        [...]     15           16
%       Filename Pitch 	MFCC1 	MFCC2 [...]     MFCC13	Label
%   'm' and 's' are 1x14 vectors.
%       m = [179.819620221498,-1.12634568636400,3.23541659384589, ..., -0.0405736669838947,-0.0107452734530379,0.0354890188765617]
%       s = [63.6436974218389,1.75493471037228,1.27452362557955,... ,0.356777158658747,0.310861718226981,0.293542497297095];
%
%
% ads = 
%   audioDatastore with properties:
% 
%                        Files: {
%                               ' ...\bhemmat\AppData\Local\Temp\an4\wav\flacData\fejs\an36-fejs-b.flac';
%                               ' ...\bhemmat\AppData\Local\Temp\an4\wav\flacData\fejs\an37-fejs-b.flac';
%                               ' ...\bhemmat\AppData\Local\Temp\an4\wav\flacData\fejs\an38-fejs-b.flac'
%                                ... and 122 more
%                               }
%                       Labels: [fejs; fejs; fejs ... and 122 more categorical]
%     AlternateFileSystemRoots: {}
%              ReadFailureRule: 'error'
%                  MaxFailures: Inf
%               OutputDataType: 'double'

ads.Files = features(:,1);
ads.AlternateFileSystemRoots = {};
ads.ReadFailureRule = 'error';
ads.MaxFailures = Inf;
ads.OutputDataType = 'double';
ads.Labels = features(:,16);

trainTestRatio = 0.8;
[ trainDatastore, testDatastore ] = mysplitEachLabel( ads, trainTestRatio );
% TODO: more test data is assigned. Fix this.

trainDatastoreCount = mycountEachLabel( trainDatastore );
testDatastoreCount = mycountEachLabel( testDatastore );

% To preview the content of the datastore, read a sample file and play it
% [ sampleTrain, info ] = read( trainDatastore );
% sound( sampleTrain, info.SampleRate );
% reset( trainDatastore );

% Unfortunately, the files are unavailable because the function to download
% the files doesn't work! The .mat file contains the features, not the
% sample data. So I'll skip these lines.

% TODO: Download the files directly from the data repository in References
% [1] and/or [2]. The file names are available in .mat, so it should be
% able to retrieve the sample data if you want.


% length( trainDatastore.Files )
% Error using tabular/length (line 189)
% Undefined function 'length' for input arguments of type 'table'.  Use the HEIGHT, WIDTH, or SIZE functions instead.
% Instead,

% Extract the features
% lenDataTrain = numel( trainDatastore.Files );
% features = cell( lenDataTrain,1);
% for i = 1: lenDataTrain
%     [dataTrain, infoTrain] = read( trainDatastore );
%     features{i} = HelperComputePitchAndMFCC( dataTrain,infoTrain );
%     
%     % Problem:
%     %   Error opening 'HelperComputePitchAndMFCC'
%     %       Undefined function or variable 'HelperComputePitchAndMFCC'.
% end
% features = vertcat( features{:} );
% features = rmmissing( features );
% head( features );   % Display the first few rows

% The above part fails to run because 'HelperComputePitchAndMFCC' is unavailable.
% Instead, 'load HelperAN4TrainingFeatures.mat' loads the features!

% Normalize the scales of the pitch and MFCC.
% Otherwise, this will bias the classifier.
% To normalize the features, subtract the mean and divide the standard
% deviation of each column.

featureVectors = features{:,2:15};  % column 1 is Filename and column 16 is Label.
m = mean(featureVectors);
s = std(featureVectors);

features{:,2:15} = (featureVectors - m) ./ s;
head( features );

% head( features )
% = 
%   8×16 table
%          Filename          Pitch      MFCC1       MFCC2       MFCC3       MFCC4       MFCC5      MFCC6       MFCC7        MFCC8       MFCC9      MFCC10       MFCC11      MFCC12      MFCC13     Label 
%     __________________    _______    ________    _______    _________    ________    _______    ________    ________    _________    _______    _________    ________    ________    ________    ______
% 
%     'an36-fejs-b.flac'    0.90535     -1.8778    0.11469      0.25866    -0.41449    0.97803    -0.34062    -0.22379    -0.031962    0.62995      0.81708    -0.29036       -0.47    -0.04532    'fejs'
%     'an36-fejs-b.flac'    0.98367     -1.8143     1.2196      0.32634    -0.65383     0.9623    -0.52854    -0.61983      0.70533    0.40654    -0.066892    -0.60354    -0.53907    -0.51924    'fejs'
%     'an36-fejs-b.flac'    0.81806     -1.4342     1.3996      0.27266    -0.77005     1.0279    -0.61349    -0.69793      0.72491    0.56842      -0.6335    -0.60484    -0.62735     -1.0637    'fejs'
%     'an36-fejs-b.flac'     0.8025     -1.1209     1.4881    0.0057061    -0.78058     1.2356     -0.7397    -0.49906       1.1048    0.39759     -0.57164    -0.36655    -0.67672    -0.87127    'fejs'
%     'an36-fejs-b.flac'    -1.0579     -1.0516     1.6394     0.026102    -0.69355      1.116    -0.85012    -0.58429      0.86925    0.83105     -0.66218    -0.84113    -0.66903    -0.60151    'fejs'
%     'an36-fejs-b.flac'    -1.0674    -0.85121     1.5999     0.074074    -0.79501     1.0355    -0.56555    -0.58294       0.5838    0.84584     -0.57511     -1.1255    -0.64767     -0.8494    'fejs'
%     'an36-fejs-b.flac'    -1.0797     -0.8476     1.4231      0.21274    -0.92891    0.82602    -0.34877    -0.20402      0.41231    0.67644     -0.56908     -1.3199    -0.43764    -0.38468    'fejs'
%     'an36-fejs-b.flac'    -1.0955    -0.75325     1.7918        0.174    -0.88856    0.65463    -0.12772    0.021446      0.56706    0.48842     -0.60995     -1.8518    -0.50805    -0.26085    'fejs'
    
% Training a Classifier

% Reformat & map the variable names etc.
inputTable = features;
predictorNames = features.Properties.VariableNames;
predictors = inputTable( :, predictorNames(2:15) );
response = inputTable.Label;

% Train a classifier
trainedClassifier = fitcknn( predictors, response,...
                            'Distance', 'euclidean', ...
                            'NumNeighbors', 5,...
                            'DistanceWeight', 'squaredinverse',...
                            'Standardize', false,...
                            'Classnames', unique(response) );
% Perform Cross-validation
k = 5;
group = (response);
c = cvpartition( group, 'KFold', k); % 5-fold stratified cross validation
partitionedModel = crossval( trainedClassifier, 'CVPartition', c);

% Compute the validation accuracy

validationAccuracy = 1 - kfoldLoss( partitionedModel, 'LossFun', 'ClassifError' );
fprintf('\nValidation accuracy = %.2f%%\n', validationAccuracy *100);
% Validation accuracy = 92.80%

% Visualize the confusion chart.
validationPredictions = kfoldPredict( partitionedModel );
figure;
cm = confusionchart( features.Label, validationPredictions, 'title', 'Validation Accuracy');
cm.ColumnSummary = 'column-normalized';
cm.RowSummary = 'row-normalized';

% Testing the Classifier
%   Test the trained KNN classifier with two speech signals from each of
%   the ten speakers to see how well it behaves. These signals are ones NOT
%   used to train the classifier.

% Extract the features
% lenDataTest = numel( testDatastore.Files );
% featuresTest = cell( lenDataTest,1);
% for i = 1: lenDataTest
%     [dataTest, infoTest] = read( testDatastore );
%     featuresTest{i} = HelperComputePitchAndMFCC( dataTest,infoTest );
%     
%     % Problem:
%     %   Error opening 'HelperComputePitchAndMFCC'
%     %       Undefined function or variable 'HelperComputePitchAndMFCC'.
% end
% featuresTest = vertcat( featuresTest{:} );
% featuresTest = rmmissing( featuresTest );

% Problem:
%   The problem with the above lines to extract the features is
%   'HelperComputePitchAndMFCC' is undefined!
% Solution?
%   Split 'features' into Train and Test with randperm!
%   Create function 'mysplitFeatures' and use it to split 'features'
%   obtained by loading the .mat file.
%   Well, there's a better instant solution. Read Solution 2 below.

% Normalize
%   Note m & s are ones computed for the training data.
%   It's legitimate to use them in order to maintain consistency in the
%   scaling or normalizing factors.

% featuresTest{:,2:15} = (featuresTest{:,2:15} - m) ./ s;
% head( featuresTest );   % Display the first few rows

% Solution 2
%   HelperAN4TestingFeatures.mat loads 'featuresTest'!!!
load HelperAN4TestingFeatures.mat

featuresTest{:,2:15} = (featuresTest{:,2:15} - m) ./ s;
head( featuresTest );   % Display the first few rows

% result = HelperTestKNNClassifier( trainedClassifier, featuresTest );
% Problem:
%   Undefined function or variable 'HelperTestKNNClassifier'.
%   I knew this would happen! But it's OK at this stage for me.
%   Assuming this works just fine. I'll just finish this example.