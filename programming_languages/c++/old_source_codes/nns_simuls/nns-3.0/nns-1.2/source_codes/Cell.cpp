 #include  "Cell.hpp"

//==============================================================================
//                     Definition of static variables
//==============================================================================
int     Cell::maxEpochs_i_;
double  Cell::targetCellError_;
string  Cell::fdInputInitialization_;
string  Cell::nnType_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
void
Cell::configure( Config& configObj, string trainingAlgorithm )
{
  assert( configObj.get_isConfigured_() );

  maxEpochs_i_           = configObj.get_cnnObj_().get_maxEpochs_i_();
  targetCellError_       = configObj.get_cnnObj_().get_targetCellError_();
  fdInputInitialization_ = configObj.get_cnnObj_().get_fdInputInitialization_();
  nnType_                = configObj.get_cnnObj_().get_nnType_();

  NeuralNetworks::configure( configObj, nnType_, maxEpochs_i_ );
  if ( trainingAlgorithm == "pso" )
    Pso::configure( configObj );  // Class TrainingAlgorithms is configured in Pso.
}
// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================

Cell::Cell()
{
  isInitialWeightMatchDone_ = false;
}


// numOfCellInputs_ basically follows the following equation.
//   numOfCellInputs_ = ( numOfAdjacencies_ + self ) * (input and output);
//
// inputDataDimension is the number of digits after reducing the input dimension.
//   The relationship with the number of input nodes to a neural network is as follows.
//
//     numOfInputNodes=inputDataDimension + 1 (bias)
//
//     where +1 is for the bias term.
//   So, the number of input nodes becomes two to include the bias.
//       MLP: raw inputs of neighbors & itself.
//      PSRN: raw inputs of neighbors & itself AND the output feedback, i.e. "+2" for the recurrence part.
//            Strictly speaking, numOfCellInputs_ should be the external inputs, but the meaning is abused here.
//      CSRN: The number of cell inputs for CSRN and MCSRN is identical. The difference is the number of
//            inputs to the neural networks.
//     MCSRN: reduces the input dimension.
//
// Note the initialization of a training algorithm should match that of neural networks.
// For PSO, this means the initial weights in the neural networks should be equal to
// the initial position of PSO's best particle.
//   The following is a relevant comment in the config file.
// pso_global_best_initial_value: inf, cnn, or any floating number.
//
//   When pso_global_best_initial_value=inf, the first particle's position becomes
// the global best's position. So pso_global_best_initial_value should be inf
// in order for PSO to work properly. Note, however, this setting is for the
// conventional neural networks.
//   On the other hand, CNN's internal behavior is so strongly interwound that
// understanding the behavior is complex. Therefore, it is often neccessary to
// start from identical initial weights in order to reduce the dynamics of starting
// from different initial weights at each run of simulations.
//   There are two modes to initialize CNN's weights (neuralnets_initial_weights_mode):
// "load_manually" and "random". For the former, "load_manually" loads initial weights
// from a file specified in "file_nn_weights". Therefore CNN can start from the
// same weights. In this context, a feature to set PSO's global best position other
// than inf is desireable.
//   For the latter, the usefulness of this feature is questionable at first sight
// because PSO randomizes CNN's weights anyways. There is a fundamental difference
// here, though. If we let PSO randomizes CNN's initial weights, what actually
// happens is PSO selects the best particle's position as initial weights. Stricly
// speaking, this initial weights are ones after one epoch of training. Letting
// PSO initialize the weights is not random strictly speaking. Therefore, even for
// the latter, CNN should allow the random CNN weights overload the initial PSO's
// best particle's position. In other words, CNN should not let PSO overtake the
// CNN's initialization. Otherwise, PSO's best particle's position after one epoch
// will mistakenly initialize CNN's weights.

void
Cell::initialize
(
  int         cellIndex,
  int         locationX,
  int         locationY,
  int         numOfAdjacencies,
  string      trainingAlgorithm,
  string      errorMetric,
  bool        matchInitialWeights,
  int         lengthOfABatchOfData
)
{
  int inputDataDimension;         // For neural networks. A dummy variable for readability
  int totalNumOfVariableWeights;  // For Pso

  index_             = cellIndex;
  locationX_         = locationX;
  locationY_         = locationY;
  numOfAdjacencies_  = numOfAdjacencies;
  numOfCellInputs_   = numOfAdjacencies + 1;  // +1 is for itself.

  isNeighborsSet_    = false;  // for setTopology();
  isHibernate_       = false;

  if ( nnType_ == "mcsrn" )
  {
    numOfCellInputs_   = ( numOfAdjacencies_ + 1 ) * 2;  // "*2" for the recurrence part.
    inputDataDimension = 2;
  }
  else
  {
    if ( nnType_ == "mlp" )
      numOfCellInputs_ = numOfAdjacencies_ + 1;
    else if ( nnType_ == "psrn" )
      numOfCellInputs_ = numOfAdjacencies_ + 2;
    else if ( nnType_ == "csrn" )
      numOfCellInputs_ = ( numOfAdjacencies_ + 1 ) * 2;  // "*2" for the recurrence part.
    else
    {
  	  cerr << "Error: This neural network type " << nnType_ << " is not supported." << endl;
  	  exit( 1 );
    }
    inputDataDimension = numOfCellInputs_;
  }

  doDynamicMemoryAllocation( errorMetric, lengthOfABatchOfData );
  nns_.initialize( inputDataDimension );
  if ( trainingAlgorithm == "pso" )
  {
	totalNumOfVariableWeights = nns_.get_totalNumOfVariableWeights_();
    assert( ( totalNumOfVariableWeights > 0 ) );
    if ( trace4dbg_ ) tout << "Cell(" << locationX_ << "," << locationY_ << ")" << endl;
    isInitialWeightMatchDone_ = pso_.initialize( totalNumOfVariableWeights, matchInitialWeights, nns_.neurons,
    		                                     nns_.get_totalNumOfLayers_(), nns_.numOfNeurons_, nns_.get_totalNumOfNeurons_() );
  }
}

void
Cell::doDynamicMemoryAllocation( string errorMetric, int lengthOfABatchOfData )
{
  int psoNumberOfParticles;
  psoNumberOfParticles  = Pso::get_numberOfParticles_();

  assert( numOfCellInputs_ );
  assert( numOfAdjacencies_ );
  assert( ( lengthOfABatchOfData > 0 ) && ( psoNumberOfParticles > 0 ) );
  assert( !errorMetric.empty() );

  neighbors_p_ = new Cell* [ numOfAdjacencies_ ];

  aBatchOfCellOutput_       = new double* [ lengthOfABatchOfData ];
  for ( int d = 0; d < lengthOfABatchOfData; d++ )
    aBatchOfCellOutput_[ d ] = new double [ psoNumberOfParticles ];
}

// Assuming aBatchOfScalarTargetData_ has been set already, set aBatchOfVectorInputData_.
// numOfCellInputs_ = numOfAdjacencies_+1;
// The bias term is added within a neural network, not in aBatchOfVectorInputData_.
// Note numOfCellInputs_ = numOfAdjacencies_ + 1; for MLP
// or numOfCellInputs_ = ( numOfAdjacencies_ + 1 ) * 2; for SRN.
void
Cell::reshape_aBatchOfScalarInputData_to_aBatchOfVectorInputData_( int lengthOfABatchOfData )
{
  if ( trace4dbg_ )
    tout << "void Cell::reshape_aBatchOfScalarInputData_to_aBatchOfVectorInputData_( int lengthOfABatchOfData )" << endl;

  assert( ( lengthOfABatchOfData > 0 ) );
  assert( numOfCellInputs_ );

  vdouble currentCellInput;

  aBatchOfVectorInputData_ = new double* [ lengthOfABatchOfData ];
  for ( int ii = 0; ii < lengthOfABatchOfData; ii++ )
    aBatchOfVectorInputData_[ ii ] = new double [ numOfCellInputs_ ];

  if ( trace4dbg_ ) tout << "  " << "Cell(" << locationX_ << "," << locationY_ <<")\t\t\t\t\t[j]"	<< endl;

  // d is an index for the raw input data.
  for ( int d = 0; d < lengthOfABatchOfData; d++)
  {
	currentCellInput = set_currentCellInput( d, fdInputInitialization_ );
	assert( !(currentCellInput.size() - numOfCellInputs_) );

	if ( trace4dbg_ ) tout << "    Cell::aBatchOfVectorInputData_[" << d << "]\t";

    for ( int jj = 0; jj < numOfCellInputs_; jj++ )
    {
      aBatchOfVectorInputData_[ d ][ jj ] = currentCellInput.at( jj );
      if ( trace4dbg_ ) tout << aBatchOfVectorInputData_[ d ][ jj ] << " ";
    }
    if ( trace4dbg_ ) tout << endl;
    // Note the bias term is added within a neural network, not here.
  }
}

void
Cell::set_isNeighborsSet_( bool value )
{
  isNeighborsSet_ =  value;
}

double
Cell::computeInitialErrors( int lengthOfABatchOfData, string errorMetric )
{
//***  tout  << " double Cell::computeInitialErrors( int lengthOfABatchOfData, string errorMetric )" << endl;

  double cellError;
  int time_o = 0;
  int time_i = 0;
  bool     traceOn  = true;

  assert( lengthOfABatchOfData > 0 );

  nns_.logInitialWeights( time_o, time_i, locationX_, locationY_, index_ );
  aBatchOfScalarOutputData_ = nns_.computeMlpOutputInBatch( time_o, time_i, aBatchOfVectorInputData_, lengthOfABatchOfData, numOfCellInputs_, index_, traceOn );

  pso_.set_p_gBest_( 0 );
//***  tout << "   "<< "aBatchOfCellOutput_[d][0]=";
  for ( int d = 0; d < lengthOfABatchOfData; d++ )
  {
    aBatchOfCellOutput_[ d ][ 0 ] = aBatchOfScalarOutputData_.at( d );
//*** tout << aBatchOfCellOutput_[ d ][ 0 ] << " ";
  }
//***  tout << endl;

  cellError  = nns_.computeError( aBatchOfScalarTargetData_, aBatchOfScalarOutputData_, lengthOfABatchOfData, errorMetric );
  lout[index_] << "\ntime_o=" << time_o << " time_i=" << time_i<< " cellError=" << cellError << endl;

  return cellError;
}

void
Cell::setNeighbor( Cell* instance, int index )
{
  neighbors_p_[ index ] = instance;
}

void
Cell::show_aBatchOfScalarInputData_( int lengthOfABatchOfData )
{
  assert( !(aBatchOfScalarInputData_.size() - lengthOfABatchOfData) );

  tout << "  Cell(" << locationX_ << "," << locationY_ << "): ";
  for ( int d = 0; d < lengthOfABatchOfData; d++)
    tout << aBatchOfScalarInputData_.at(d) << " ";
  tout << endl;
}

void
Cell::show_aBatchOfVectorInputData_( int lengthOfABatchOfData )
{
//  assert( !(aBatchOfVectorInputData_.size() - lengthOfABatchOfData) ); aBatchOfVectorInputData_ is a matrix. TODO: Fix this later.

  tout << "  Cell(" << locationX_ << "," << locationY_ << ")" << endl;
  for ( int jj = 0; jj < numOfCellInputs_; jj++ )
  {
    tout << "    ";
    for ( int d = 0; d < lengthOfABatchOfData; d++)
      tout << aBatchOfVectorInputData_[ d ][ jj ] << " ";
    tout << endl;
  }
}

void
Cell::show_aBatchOfScalarTargetData_( int lengthOfABatchOfData )
{
  assert( !(aBatchOfScalarTargetData_.size() - lengthOfABatchOfData) );

  tout << "  Cell(" << locationX_ << "," << locationY_ << "): ";
  for ( int d = 0; d < lengthOfABatchOfData; d++)
    tout << aBatchOfScalarTargetData_.at(d) << " ";
  tout << endl;
}

void
Cell::showNeighbors( int x, int y )
{
  assert( isNeighborsSet_ );

  lout[index_] << "# Cell(" << x << "," << y << ")'s neighbors: ";
  for ( int aa = 0; aa < numOfAdjacencies_; aa++ )
    lout[index_] << "cell " << neighbors_p_[ aa ]->get_index_() << " ";
  lout[index_] << endl;
}

int
Cell::get_index_() const
{
  return index_;
}

int
Cell::get_numOfAdjacencies_() const
{
  return numOfAdjacencies_;
}

int
Cell::get_numOfCellInputs_() const
{
  return numOfCellInputs_;
}

bool
Cell::get_isHibernate_() const
{
  return isHibernate_;
}

bool
Cell::get_isNeighborsSet_() const
{
  return isNeighborsSet_;
}

double
Cell::get_aBatchOfCellOutput_( int index, int particle ) const
{
  return aBatchOfCellOutput_[ index ][ particle ];
}

double
Cell::get_targetData_( int index ) const
{
  return aBatchOfScalarTargetData_[ index ];
}

int
Cell::get_maxEpochs_i_() const
{
  return maxEpochs_i_;
}

vdouble
Cell::get_cellError_() const
{
  return cellError_;
}

int
Cell::get_locationX_() const
{
  return locationX_;
}

int
Cell::get_locationY_() const
{
  return locationY_;
}

bool
Cell::get_isInitialWeightMatchDone_() const
{
  return isInitialWeightMatchDone_;
}

NeuralNetworks&
Cell::get_nns_()
{
  return nns_;
}

Pso&
Cell::get_pso_()
{
  return pso_;
}

// When this cell is chosen, get the output for all the input data
// or in batch.
// CSRN (Cellular Simultaneous Recurrent Network)
// MCSRN (Modified CSRN) with input dimension reduction for a 2x2 board.

double
Cell::trainInBatchMode( int time_o, string errorMetric, int lengthOfABatchOfData  )
{
  double cellError;

//***  show_aBatchOfVectorInputData_( lengthOfABatchOfData );
//***  show_aBatchOfScalarTargetData_( lengthOfABatchOfData );

  if ( nnType_ == "mcsrn" || nnType_ == "csrn" )
  {
	// The conventional PSO does not clear up the old history of pBests when the feedback input changes.
    if ( pso_.get_useParticleHistoryReset_() )
      aBatchOfScalarOutputData_ = nns_.runSrnRpso( time_o, aBatchOfVectorInputData_, aBatchOfScalarTargetData_, pso_, maxEpochs_i_, numOfCellInputs_, targetCellError_, errorMetric, lengthOfABatchOfData, index_ );
    else
	  aBatchOfScalarOutputData_ = nns_.runSrnPso( time_o, aBatchOfVectorInputData_, aBatchOfScalarTargetData_, pso_, maxEpochs_i_, numOfCellInputs_, targetCellError_, errorMetric, lengthOfABatchOfData, index_ );
  }
  else if ( nnType_ == "mlp" )
    aBatchOfScalarOutputData_ = nns_.runMlpPso( lengthOfABatchOfData );
  else if ( nnType_ == "prsn" )
    aBatchOfScalarOutputData_ = nns_.runPsrnPso( lengthOfABatchOfData );
  else
  {
	  cerr << "Error: double Cell::trainInBatchMode( double*** aBatchOfCnnOutput )" << endl;
	  exit( 1 );
  }
  cellError = nns_.get_error_();
  cellError_.push_back( cellError );

//  if ( cellError <= targetCellError_ )
//  {
//    isHibernate_ = true;
//    lout[index_] << "Cell(" << locationX_ << "," << locationY_ << ") is hibernated!" << endl;
//  }

  return cellError;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

// numOfCellInputs_ =   numOfAdjacencies_ + 1,       for MLP
//                      numOfAdjacencies_ + 2,       for PSRN
//                    ( numOfAdjacencies_ + 1 ) * 2, for CSRN
vdouble
Cell::set_currentCellInput( int d, string fdInputInitialization )
{
  assert( isNeighborsSet_ );

  vdouble currentCellInput;
  double  tmp;  // A dummy variable is used for debugging purposes.
  int     index;

  for ( int ii = 0; ii < numOfCellInputs_; ii++ )
  {
    if ( ii == 0 )  // Set the raw input for this cell.
      tmp = aBatchOfScalarInputData_.at( d );
    else if ( ii < numOfAdjacencies_ + 1 )  // Set the raw input from neighboring cells.
      tmp = neighbors_p_[ ii - 1 ]->aBatchOfScalarInputData_.at( d );

    // The following part is for PSRN & CSRN.
    // We don't need the if statement such as "if ( nnType_ == PSRN )"
    // because the if statement stops before.
    else if ( ii == numOfCellInputs_ - 1 )
    { // The last one is the feedback output from this cell.
      if ( fdInputInitialization == "zeros")
        tmp = 0.0;
      else if ( fdInputInitialization == "ones")
        tmp = 1.0;
      else if ( fdInputInitialization == "random")
        tmp = rvs_.uniform();  // A floating point number ranging from [0,1]
      else if ( fdInputInitialization == "rand_ternary")
      {
        // An integer: 0,1,2.
        //tmp = static_cast<int> ( floor( 3.0 * rvs_.uniform() ) );
        tmp = floor( 3.0 * rvs_.uniform() );
      }
      else if ( fdInputInitialization == "target")
        tmp = aBatchOfScalarTargetData_[d];
    }
    // The following else statement should be applied only to the CSRN case.
    else
    { // The rest of them are the feedback output from the neighboring cells.
      if ( fdInputInitialization == "zeros")
        tmp = 0.0;
      else if ( fdInputInitialization == "ones")
        tmp = 1.0;
      else if ( fdInputInitialization == "random")
        tmp = rvs_.uniform();  // A floating point number ranging from [0,1]
      else if ( fdInputInitialization == "rand_ternary")
      {
        // An integer: 0,1,2.
        //tmp = static_cast<int> ( floor( 3.0 * rvs_.uniform() ) );
        tmp = floor( 3.0 * rvs_.uniform() );
      }
      else if ( fdInputInitialization == "target")
      {
        index = ii -  static_cast<int> ( numOfCellInputs_ / 2 );
        tmp = neighbors_p_[ index ]->get_targetData_( d );
      }
    }
    currentCellInput.push_back( tmp );
  }
  return currentCellInput;
}

// MSE (Mean Squared Error) = sumOfSe / lengthOfABatchOfData
double
Cell::computeMseInBatch( int p, int lengthOfABatchOfData )
{
  double sumOfSe; // SE (Squared Error)
  double mse;
  sumOfSe = 0;
  for ( int d = 0; d < lengthOfABatchOfData; d++ )
  {
    sumOfSe += ( aBatchOfScalarTargetData_[ d ] - aBatchOfCellOutput_[ d ][ p ] )
             * ( aBatchOfScalarTargetData_[ d ] - aBatchOfCellOutput_[ d ][ p ] );
             
      cout << "f\t"
           << "Cell::computeMseInBatch\t"
           << "p:d\t" << p << ":" << d << "\t"
           << "sumOfSe\t" << sumOfSe << "\t"
           << "=(" << aBatchOfScalarTargetData_[ d ] << "-"
           << aBatchOfCellOutput_[ d ][ p ] << ")^2"
           << endl;
  }
  mse = sumOfSe / lengthOfABatchOfData;
      cout << "f\t"
           << "Cell::computeMseInBatch\t"
           << "mse\t" << mse << "\t"
           << "=" << sumOfSe << "/"
           << lengthOfABatchOfData
           << endl;

  return ( mse );
}

// Place the neighboring cells' outputs as the feedback inputs to the cells
// The first three slots, aBatchOfVectorInputData_[d][0],aBatchOfVectorInputData_[d][1],aBatchOfVectorInputData_[d][],
// contain the raw board status. These vales don't change.
//   On the other hand, the last three slots are occupied by the cell outputs.
// These need to be updated frequently, and the updates are done below.
//
// Design issue: The input arguments "int numOfAdjacencies, int lengthOfABatchOfData" are
//   actually not neccessary. But this will increase the readability of the code, so
//   leave them as they are.

// This function is used in a function NeuralNetworks::runSrnPso(...).

void
Cell::update_aBatchOfVectorInputData_by_fetchingNeighborsCellOutputs( int lengthOfABatchOfData, double*** aBatchOfCnnOutput )
{
  int x, y;
  int i;

  for ( int aa = 0; aa < numOfAdjacencies_; aa++ )
  {
    x = neighbors_p_[ aa ]->get_locationX_();
    y = neighbors_p_[ aa ]->get_locationY_();
    i = numOfCellInputs_/2 + aa;  // numOfCellInputs_/2 = 3 when numOfCellInputs_=6
    for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      aBatchOfVectorInputData_[ d ][ i ] = aBatchOfCnnOutput[ d ][ x ][ y ];
    }
  }
}
