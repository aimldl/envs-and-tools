#include  "Cnn.hpp"

int			Cnn::maxEpochs_o_;
bool		Cnn::isConfigDone_;
bool		Cnn::matchNnInitialWeightsToTrainingAlgo_;
double		Cnn::targetSystemError_;
string		Cnn::errorMetric_;
string      Cnn::trainingAlgorithm_;

//   The input arguments are actually not neccessary, but using them helps to read the code.

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!
//
// Configure simulation settings
// Now, the configuration file is read.
// Given those parameters, configure simulation-related settings.
// For example, input data type.
//
// Functions and variables in this part should be static
// because they are called before their class are instantiated.

void		Cnn::configure( Config& configObj )
{
  assert( configObj.get_isConfigured_() );

  int numOfCells;

  maxEpochs_o_                         = configObj.get_cnnObj_().get_maxEpoch_o_();
  targetSystemError_                   = configObj.get_cnnObj_().get_targetSystemError_();
  matchNnInitialWeightsToTrainingAlgo_ = configObj.get_cnnObj_().get_matchNnInitialWeightsToTrainingAlgo_();
  errorMetric_                         = configObj.get_cnnObj_().get_errorMetric_();
  trainingAlgorithm_                   = configObj.get_cnnObj_().get_trainingAlgorithm_();

  numOfCells = configObj.get_simulationsObj_().get_boardSize_()*configObj.get_simulationsObj_().get_boardSize_();

  Error4Cnn::configure( numOfCells );
  Cell::configure( configObj, trainingAlgorithm_ );

  isConfigDone_ = true;
}

// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

Cnn::Cnn()
{
  assert( isConfigDone_ );
  isBadukDataReformatted_ = false;
}

Cnn::Cnn( BadukData& badukDataObj )
{
  assert( isConfigDone_ );
  assert( badukDataObj.get_isInitialized_() );

  isBadukDataReformatted_ = false;
  initialize( badukDataObj );
}

Cnn::~Cnn()
{
}

// Call this function in the constructor of a derived class.
// Why? It's just easier to understand the code.

// This function is the primary part to initialize all the classes.
void
Cnn::initialize( BadukData& badukDataObj )
{
  assert( badukDataObj.get_isConfigured_() );

  int boardSizeX, boardSizeY;
  int lengthOfABatchOfData;

  boardSizeX           = badukDataObj.get_boardSizeX_();
  boardSizeY           = badukDataObj.get_boardSizeY_();
  lengthOfABatchOfData = badukDataObj.get_lengthOfABatchOfData_();

  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  initialize_cells_( trainingAlgorithm_, boardSizeX, boardSizeY, lengthOfABatchOfData );
  setMeshTopology( boardSizeX, boardSizeY );
  splitBadukDataIntoDataInCells( badukDataObj, boardSizeX, boardSizeY, lengthOfABatchOfData );
  allocateMemory_aBatchOfCnnOutput_( boardSizeX, boardSizeY, lengthOfABatchOfData );

  saveInitialWeightsInCells( boardSizeX, boardSizeY );
  showNeighborsInCells( boardSizeX, boardSizeY );
  showDataInCells( boardSizeX, boardSizeY, lengthOfABatchOfData );
}

// assert( isInitialWeightMatchDoneInAllCells() );
//   Neural networks' initial weights in all cells should be matched to the initial
// values of all the instances of the training algorithm.
//   This part is redundant if the program works as it's supposed to be designed.
// The Neural network's initial weights should match the initial values in the
// training algorithm. For PSO, this function matches the Cnn's initial weights
// to PSO's best particle's position. In other words, the weights become the
// initial position of the best particle.
//   The Cnn's initial weights can either be randomized or manually loaded from
// an external textfile. These initial weights should be matched to the training
// algorithm.
//   Let's take an example of PSO to explain the neccessity of this process.
// PSO randomizes the particles' potisions, which correspond to Cnn's weights.
// Without matching the initial weights to PSO's best particle's position, the initial
// weights are meaningless because the PSO's best particle's position will be
// overwritten immediately.
//   Then the question is what's the use of the initial weights. Are the initial
// weights really neccessary? The answer is yes to me because CNN has such a complex
// structure that the training is extremely difficult. In order to understand the
// internal behavior of CNN, starting from a fixed initial weights can help
// cultivating the insights to the behavior.
//
// Design issue: update_aBatchOfCnnOutput_( boardSizeX, boardSizeY, lengthOfABatchOfData );
//   This function is extremely important to emulate the CNN's behavior because it
//   synchronizes all the CNN outputs. The location of this function is changed.
//
// Formerly, the outer loop was as follows.
//
// OLD CODE:
//   TODO: change the following for a pseudocode.
//
//   terminalConditionNotMetOuterLoop  = true;
//   time_o_ = 0;
//   while ( terminalConditionNotMetOuterLoop )
//   {
//     systemError = 0.0;
//     for ( int x = 0; x < boardSizeX; x++ )
//     {
//       for ( int y = 0; y < boardSizeY; y++ )
//       {
//     	  cellError = 0.0;
//         if ( !cells_[ x ][ y ].get_isHibernate_() )
//           cellError = cells_[ x ][ y ].trainInBatchMode( aBatchOfCnnOutput_, time_o_, errorMetric_, lengthOfABatchOfData );
//         systemError += cellError;
//       }
//     }
//     update_aBatchOfCnnOutput_( boardSizeX, boardSizeY, lengthOfABatchOfData );
//     terminalConditionNotMetOuterLoop = ( time_o_ < maxEpochs_o_ ) && ( systemError > targetSystemError_ );
//     time_o_++;
//   }
//
//   This looks fine, but there is a problem because of the inner loop.
// At the first epoch of the outer loop, the training is already in proress, so it's difficult to
// find the very initial system error. An extreme case is that the number of the inner loop is so large
// that the training is completed and the target system error is reached at the very first epoch of the outer
// loop. This problem can be solved by computing the very initial error before the outer loop actually starts.
//   The introduction of function computeInitialErrors forces to relocate function update_aBatchOfCnnOutput_
// BEFORE the inner loops starts. In other words, the structure changes as follows.
//
// NEW CODE:
//   TODO: change the following for a pseudocode.
//
//   terminalConditionNotMetOuterLoop  = true;
//   time_o_ = 0;
//   computeInitialErrors( errorMetric_, boardSizeX, boardSizeY, lengthOfABatchOfData );
//   while ( terminalConditionNotMetOuterLoop )
//   {
//     systemError = 0.0;
//     update_aBatchOfCnnOutput_( boardSizeX, boardSizeY, lengthOfABatchOfData );
//     for ( int x = 0; x < boardSizeX; x++ )
//     {
//       for ( int y = 0; y < boardSizeY; y++ )
//       {
//     	  cellError = 0.0;
//         if ( !cells_[ x ][ y ].get_isHibernate_() )
//           cellError = cells_[ x ][ y ].trainInBatchMode( aBatchOfCnnOutput_, time_o_, errorMetric_, lengthOfABatchOfData );
//         systemError += cellError;
//       }
//     }
//     terminalConditionNotMetOuterLoop = ( time_o_ < maxEpochs_o_ ) && ( systemError > targetSystemError_ );
//     time_o_++;
//   }
//
// Then the question is why function update_aBatchOfCnnOutput_ should be called BEFORE the inner loop.
// The feedback loops (outer and inner loops) complicates the pseudocode structure and are prone to mulfunctioning
// of the CSRN. For example, the cell output is not properly passed to the feedback input, etc.
//   Note the CSRN's output has already been updated by computeInitialErrors before the first run of the inner loop.
// What does this mean? After running function computeInitialErrors once, the CSRN has a new batch of cell output.
// Note that this new batch of output should be the second part of a batch of vector input data for neural networks.
//   To summarize, a batch of scalar input data remains identicall all the time one the BadukData is split into
// the CNN format. On the other hand, a batch of scalar output data from cells or a CNN is being updated after one
// iteration of the outer loop. This update changes a part of a batch of vector input data for neural networks within
// cells. In order to emulate CNN correctly, all the cells need to be synchronized correctly so that the values of
// the feedback of cell outputs are correctly assigned as the neural networks inputs. If this feedback value assignment
// is wrong, the CNN doesn't work properly. So a caution needs to be paid when all the cells are synchronized.

void
Cnn::runSimulation( bool showProgressBar, int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  bool    terminalConditionNotMetOuterLoop;
  double  systemError;
  double  cellError;
  int     resolution, numOfBars;  // PROGRESS BAR
  double  resolDivisor;           // PROGRESS BAR
  vdouble cellErrors;

  if ( showProgressBar )
  {
	resolDivisor = 20.0;  // The progress bar has about 20 bins to show the progress. 100 is too long to display in the terminal.
    resolution   = ( int ) ceil( ( double ) maxEpochs_o_ / resolDivisor );
    numOfBars    = ( int ) ( double ) maxEpochs_o_ / ( double ) resolution;

    cout << "\n  Running a simulation..." << "\n    0%";
    for ( int i = 0; i < numOfBars; i++ )
      cout << "   ";
    cout << "100%" << "\n    |";
  }

  terminalConditionNotMetOuterLoop  = true;  // If true, next loop; o.w., loop is over.
  time_o_ = 0;

  assert( isInitialWeightMatchDoneInAllCells( boardSizeX, boardSizeY ) );
  computeInitialErrors( boardSizeX, boardSizeY, lengthOfABatchOfData );  // errorMetric_ is either abs_error or mse.
  while ( terminalConditionNotMetOuterLoop )
  {
    systemError = 0.0;
    cellErrors.clear();
    update_aBatchOfCnnOutput_( boardSizeX, boardSizeY, lengthOfABatchOfData );  // Important to synchronize all the CNN outputs to emulate CSRN's feature.
    for ( int x = 0; x < boardSizeX; x++ )
    {
      for ( int y = 0; y < boardSizeY; y++ )
      {
    	// If the cell is hibernated, stop training the cell. Otherwise, keep training the cell.
      	// Note no error should be added to the system error when a cell hibernates.
    	cellError = 0.0;  // This line neccessary when a cell hibernates!!!
        if ( !cells_[ x ][ y ].get_isHibernate_() )  // Currently, hibernation is disabled.
        {
          cells_[ x ][ y ].update_aBatchOfVectorInputData_by_fetchingNeighborsCellOutputs( lengthOfABatchOfData, aBatchOfCnnOutput_ );
          cellError = cells_[ x ][ y ].trainInBatchMode( time_o_, errorMetric_, lengthOfABatchOfData );
          lout[ cells_[ x ][ y ].get_index_() ] << "time_o_=" << time_o_ << "\tcellError = " << cellError << endl;
        }
        cellErrors.push_back(cellError);  // This should be outside the if statement. When cellError is zero (target Error), a cell hibernates.
        systemError += cellError;
      }
    }
    error_.push_back( Error4Cnn( time_o_, systemError, cellErrors ) );
    systemError_.push_back( systemError );
    terminalConditionNotMetOuterLoop = ( time_o_ < maxEpochs_o_ ) && ( systemError > targetSystemError_ );

    for ( int x = 0; x < boardSizeX; x++ )
      for ( int y = 0; y < boardSizeY; y++ )
        lout[ cells_[ x ][ y ].get_index_() ] << "time_o_=" << time_o_ << "\tsystemError= " << systemError << endl;

    if ( showProgressBar )
      if ( ( time_o_ % resolution ) == 0 )  cout << "===";
    time_o_++;
  }
  if ( showProgressBar )
    cout << "|\n" << "  Simulation is done." << endl;
}

void
Cnn::logErrors( int boardSizeX, int boardSizeY )
{
  int   numOfCells;
  int   time_i_max;
  int   x_max (0), y_max (0);
  int** time_i = new int* [ boardSizeX ];
  for ( int x = 0; x < boardSizeX; x++ )
    time_i [ x ] = new int [ boardSizeY ];

  numOfCells = error_[ 0 ].numOfCells_;

  eout << "# \tSystem\tCell Error\n"
       << "# Time\tError";
  for ( int c = 0; c < numOfCells; c++ )
    eout << "\t" << c ;
  eout << endl;
  eout << "#####################################################\n";

  for ( int time_o=0; time_o < error_.size(); time_o++ )
  {
    // Design issue: Use error_[ time_o ].time_o, not time_o_ just in case a mistake is made.
    eout << error_[ time_o ].time_o_ << "\t" << error_[ time_o ].systemError_;
    for ( int c = 0; c < numOfCells; c++ )
      eout << "\t" << error_[ time_o ].aVectorOfCellError_[ c ];
    eout << endl;
  }

  eout << "#####################################################\n"
       << "# Error profile wrt. time_o and time_i\n"
       << "# \t\tcellErrors\n"
       << "# t_o\tt_i";
  for ( int c = 0; c < numOfCells; c++ )
    eout << "\t" << c ;
  eout << "\n#####################################################\n";

  time_i_max = 0;
  for ( int x = 0; x < boardSizeX; x++ )
    for ( int y = 0; y < boardSizeY; y++ )
    {
      time_i[x][y] = cells_[x][y].get_nns_().get_errors_().size();
//      cout << "time_i[" << x <<"][" << y << "]=" << time_i[x][y] << endl;
      if ( time_i_max < cells_[x][y].get_nns_().get_errors_().size() )
      {   // Get the largest size.
        time_i_max = time_i[x][y];
        x_max = x;
        y_max = y;
      }
    }

  for ( int t_i = 0; t_i < time_i_max; t_i++ )
  {
    eout << cells_[x_max][y_max].get_nns_().get_errors_().at( t_i ).time_o_
     	 << "\t" << cells_[x_max][y_max].get_nns_().get_errors_().at( t_i ).time_i_;
    for ( int x = 0; x < boardSizeX; x++ )
      for ( int y = 0; y < boardSizeY; y++ )
      {
    	if ( time_i[x][y] > t_i )
    	  eout << "\t" << cells_[x][y].get_nns_().get_errors_().at( t_i ).error_;
    	else
    	  eout << "\t" << "0";
      }
	eout << endl;
  }

  for ( int x = 0; x < boardSizeX; x++ )
    delete [] time_i [ x ];
  delete [] time_i;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

//  The input data is in a sequence of matrices. For example,
//    1 0
//    0 0
//    ----
//    0 0
//    1 0
//    ----
//     ...
//    ----
//    1 1
//    1 0
//    ----
//    1 1
//    1 1
//    ----
//  When these matrices are reformatted,
//
//    1 1 ... 0 1  <== for (1,1)
//    1 1 ... 1 0  <== for (1,2)
//    1 1 ... 0 0  <== for (2,1)
//    1 0 ... 0 0  <== for (2,2)
//
//  A sequence on the top should be stored in a cell at (1,1).
//  Another sequence on the second row in a cell at (1,2), and so on.

// restructure the input data. Note the int type input_Data_ is casted to double.

// aBatchOfVectorInputData_ in all the cells are fixed during training. So, set them just once outside the while loop in trainWtPso().
// Reshape data for cells.
// Design issue:
//   Initialize aBatchOfVectorInputData_ AFTER aBatchOfScalarTargetData_ because aBatchOfScalarTargetData_ may be
//   called in reshape_aBatchOfScalarInputData_to_aBatchOfVectorInputData_() when cnn_fd_input_initialization = target.

void
Cnn::splitBadukDataIntoDataInCells( BadukData& badukDataObj, int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  assert( isTopologySet_ );
  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  double tmpInputData, tmpTargetData;

  for ( int x = 0; x < boardSizeX; x++ )
  {
    for ( int y = 0; y < boardSizeY; y++ )
    {
      /////////////////////////////////////////////////////////////
      for ( int d = 0; d < lengthOfABatchOfData; d++ )
      {
    	// TODO: use get_aBatchOfScalarInputData_() instead of aBatchOfScalarInputData_.
        tmpInputData = static_cast<double>
                     ( badukDataObj.get_aPrioriBoard_()[ x ][ y ][ d ] );
        tmpTargetData = static_cast<double>
                     ( badukDataObj.get_aPosterioriBoard_()[ x ][ y ][ d ] );

        cells_[x][y].aBatchOfScalarInputData_.push_back( tmpInputData );
        cells_[x][y].aBatchOfScalarTargetData_.push_back( tmpTargetData );
      }
      /////////////////////////////////////////////////////////////
    }
  }
  isBadukDataReformatted_ = true;

  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      cells_[ x ][ y ].reshape_aBatchOfScalarInputData_to_aBatchOfVectorInputData_( lengthOfABatchOfData );
  // Note aBatchOfScalarTargetData_ doesn't have to be reshaped.
}

void
Cnn::allocateMemory_aBatchOfCnnOutput_( int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  aBatchOfCnnOutput_ = new double** [ lengthOfABatchOfData ];
  for ( int d = 0; d < lengthOfABatchOfData; d++ )
  {
    aBatchOfCnnOutput_[ d ] = new double* [ boardSizeX ];
    for ( int x = 0; x < boardSizeX; x++ )
      aBatchOfCnnOutput_[ d ][ x ] = new double [ boardSizeY ];
  }
}

// Initializing cells involves with initialization of classes declared in a Cell.

void
Cnn::initialize_cells_( string trainingAlgorithm, int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  int numOfAdjacencies;
  int cellIndex;

  cells_ = new Cell*[ boardSizeX ];
  for ( int ii = 0; ii < boardSizeX ; ii++ )
    cells_[ ii ] = new Cell[ boardSizeY ];

  cellIndex = 0;
  for ( int x = 0; x < boardSizeX ; x++ )
  {
    for ( int y = 0; y < boardSizeY ; y++ )
    {
      numOfAdjacencies = determine_numOfAdjacencies( x, y, boardSizeX, boardSizeY );
      cells_[ x ][ y ].initialize( cellIndex, x, y, numOfAdjacencies, trainingAlgorithm,
                                   errorMetric_, matchNnInitialWeightsToTrainingAlgo_,
                                   lengthOfABatchOfData );
      cellIndex++;
    }
  }
}

// numOfAdjacencies = 2 at the four corners of a board.
// numOfAdjacencies = 3 on the border of a board (except the corners)
// numOfAdjacencies = 4 at the rest of locations on a board.

int
Cnn::determine_numOfAdjacencies( int x, int y, int boardSizeX, int boardSizeY )
{
  int numOfAdjacencies;

  if ( ( x == 0            && y == 0 ) || ( x == 0            && y == boardSizeY-1 ) ||
       ( x == boardSizeX-1 && y == 0 ) || ( x == boardSizeX-1 && y == boardSizeY-1 ) )
    numOfAdjacencies = 2;
  else if ( x == 0 || y == 0 || x == boardSizeX-1 || y == boardSizeY-1 )
    numOfAdjacencies = 3;
  else
    numOfAdjacencies = 4;

  return numOfAdjacencies;
}

// void Cnn::setMeshTopology()
//   sets a mesh topology by specifying neighboring cells.
//
//   The input arguments are actually not neccessary, but using them helps to read the code.

void
Cnn::setMeshTopology( int boardSizeX, int boardSizeY )
{
  assert( ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  for ( int x = 0; x < boardSizeX ; x++ )
  {
    for ( int y = 0; y < boardSizeY ; y++ )
    {
      assert( !cells_[ x ][ y ].get_isNeighborsSet_() ); // should be false.
      if ( x == 0 && y == 0 )
      {
        cells_[ x ][ y ].setNeighbor( &cells_[ 0 ][ 1 ], 0 );
        cells_[ x ][ y ].setNeighbor( &cells_[ 1 ][ 0 ], 1 );
        cells_[ x ][ y ].set_isNeighborsSet_( true );
      }
      else if ( x == 0 && y == 1 )
      {
        cells_[ x ][ y ].setNeighbor( &cells_[ 1 ][ 1 ], 0 );
        cells_[ x ][ y ].setNeighbor( &cells_[ 0 ][ 0 ], 1 );
        cells_[ x ][ y ].set_isNeighborsSet_( true );
      }
      else if ( x == 1 && y == 0 )
      {
        cells_[ x ][ y ].setNeighbor( &cells_[ 1 ][ 1 ], 0 );
        cells_[ x ][ y ].setNeighbor( &cells_[ 0 ][ 0 ], 1 );
        cells_[ x ][ y ].set_isNeighborsSet_( true );
      }
      else if ( x == 1 && y == 1 )
      {
        cells_[ x ][ y ].setNeighbor( &cells_[ 1 ][ 0 ], 0 );
        cells_[ x ][ y ].setNeighbor( &cells_[ 0 ][ 1 ], 1 );
        cells_[ x ][ y ].set_isNeighborsSet_( true );
      }
    }
  }
  isTopologySet_ = true;
}

// Why saveInitialWeightsInCells is created?
//   When the neural networks' weights are initialized, they are randomized each time.
// This means the weights at each run of simulations are randomized.
// This randomization complicates the process to analyze the internal behavior of CNN.
// So it is neccessary to save and load initial weights so repeated experiments can be performed.
//
// Design issue:
//   Using a single function as follows is more intuitive thant saving weights at many instances of
// classes such as NeuralNetworks, Neuron, etc even if it may run slower. Saving weights occurs only
// once, so I believe it won't slow down the run time too much compared to saving weights separately.

void
Cnn::saveInitialWeightsInCells( int boardSizeX, int boardSizeY )
{
  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      cells_[ x ][ y ].get_nns_().saveInitialWeights(x,y);
}

void
Cnn::showNeighborsInCells( int boardSizeX, int boardSizeY )
{
  assert( isTopologySet_ );

  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      cells_[ x ][ y ].showNeighbors(x, y);
}

void
Cnn::showDataInCells( int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  tout << "void Cell::show_aBatchOfScalarInputData_( int lengthOfABatchOfData )" << endl;
  for ( int x = 0; x < boardSizeX ; x++ )
      for ( int y = 0; y < boardSizeY ; y++ )
        cells_[ x ][ y ].show_aBatchOfScalarInputData_( lengthOfABatchOfData );

  tout << "void Cell::show_aBatchOfVectorInputData_( int lengthOfABatchOfData )" << endl;
  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      cells_[ x ][ y ].show_aBatchOfVectorInputData_( lengthOfABatchOfData );

  tout << "void Cell::show_aBatchOfScalarTargetData_( int lengthOfABatchOfData )" << endl;
  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      cells_[ x ][ y ].show_aBatchOfScalarTargetData_( lengthOfABatchOfData );
}

// aBatchOfCnnOutput is a temporary storage to store the CNN output
// at a specific epoch. It doesn't really matter for CMLP, but does matter
// for CSRN. For the latter, note the outputs in CNN are exchanged only at
// the outter loop. When the outputs are exchanged in the inner loop,
// the CNN operation is messed up asynchronously.

void
Cnn::update_aBatchOfCnnOutput_( int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  int indexPsoGBestParticle;

  for ( int d = 0; d < lengthOfABatchOfData; d++)
    for ( int x = 0; x < boardSizeX ; x++ )
      for ( int y = 0; y < boardSizeY ; y++ )
      {
    	indexPsoGBestParticle = cells_[ x ][ y ].get_pso_().get_p_gBest_();
    	assert( !( indexPsoGBestParticle == -1 ) );  // indexPsoGBestParticle should not be -1.
        aBatchOfCnnOutput_[ d ][ x ][ y ] = cells_[ x ][ y ].get_aBatchOfCellOutput_( d, indexPsoGBestParticle );
      }
}
// Errors from the initial CNN weights or the initial errors are computed here.
// The reason why the initial errors are neccessary is two-fold.
//   First, it is hard to know how much improvement in errors is made at the first epoch.
// CSRN trained with PSO goes through two factors to improve the errors.
//   Factor 1: Internal loop by the reccurence part in CSRN.
//   Factor 2: The multiple number of PSO particles
// In order to compare the improvement to a case without any cause of improvement,
// initial errors are neccessary.
//
// System errors are computed by adding up all cell errors for all the inputdata.
// A cell error is the difference between a cell's estimated output and the target data.

void
Cnn::computeInitialErrors( int boardSizeX, int boardSizeY, int lengthOfABatchOfData )
{
  assert( ( lengthOfABatchOfData > 0 ) && ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  int     time_o = 0;
  vdouble cellErrors;
  double  systemError = 0.0;
  double  cellError =0.0;       // Absolute Error

  for ( int x = 0; x < boardSizeX ; x++ )
  {
    for ( int y = 0; y < boardSizeY ; y++ )
    {
      cellError = cells_[ x ][ y ].computeInitialErrors( lengthOfABatchOfData, errorMetric_ );
      cellErrors.push_back(cellError);
      systemError += cellError;

      lout[ cells_[ x ][ y ].get_index_() ] << "time_o_=" << time_o_ << "\tcellError = " << cellError << endl;
    }
  }

  for ( int x = 0; x < boardSizeX ; x++ )
    for ( int y = 0; y < boardSizeY ; y++ )
      lout[ cells_[ x ][ y ].get_index_() ] << "time_o_=" << time_o_ << "\tsystemError= " << systemError << endl;

  error_.push_back( Error4Cnn( time_o, systemError, cellErrors ) );
}

// This function returns true only if all the cells are done initial weight match.
// In other words, it returns false if any of the cells return false from
// cells_[ x ][ y ].get_isInitialWeightMatchDone_()

bool
Cnn::isInitialWeightMatchDoneInAllCells( int boardSizeX, int boardSizeY )
{
  bool matchDone;

  matchDone = true;
  for ( int x = 0; x < boardSizeX; x++ )
  {
    for ( int y = 0; y < boardSizeY; y++ )
    {
      if ( !cells_[ x ][ y ].get_isInitialWeightMatchDone_() )
      {
    	  matchDone = false;
      }
    }
  }
  return matchDone;
}
