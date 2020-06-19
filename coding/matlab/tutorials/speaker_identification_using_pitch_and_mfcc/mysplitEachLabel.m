function [ trainDatastore, testDatastore ] = mysplitEachLabel( ads, trainTestRatio )

    %assert( numel( ads.Files ) - numel( ads.Labels )  );  % The size of both Files & Labels is assumed to be equal.
    % TODO: Fix this
    %     Error using assert
    %     The condition input argument must be a scalar logical.

    totalNumOfData = numel( ads.Files );
    numOfTrainData = ceil( totalNumOfData * trainTestRatio );
    
    % Get the randomized index
    idx = randperm( totalNumOfData );
    
    trainDatastore.Files    = ads.Files( idx( 1:numOfTrainData ), : );
    testDatastore.Files      = ads.Files( idx( numOfTrainData+1:end ), : );
    
    trainDatastore.Labels  = ads.Labels( idx( 1:numOfTrainData ), : );
    testDatastore.Labels    = ads.Labels( idx( numOfTrainData+1 ):end, : );

    % Copy the rest of variables
    trainDatastore.AlternateFileSystemRoots = ads.AlternateFileSystemRoots;
    trainDatastore.ReadFailureRule              = ads.ReadFailureRule;
    trainDatastore.MaxFailures                    = ads.MaxFailures;
    trainDatastore.OutputDataType              = ads.OutputDataType;

    testDatastore.AlternateFileSystemRoots = ads.AlternateFileSystemRoots;
    testDatastore.ReadFailureRule              = ads.ReadFailureRule;
    testDatastore.MaxFailures                    = ads.MaxFailures;
    testDatastore.OutputDataType              = ads.OutputDataType;

end