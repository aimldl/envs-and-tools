#include  "NeuralNetworks.hpp"

//==============================================================================
//                     Definition of static variables
//==============================================================================
int		NeuralNetworks::totalNumOfLayers_;
int		NeuralNetworks::totalNumOfNeurons_;
int		NeuralNetworks::activationFunction_;
string	NeuralNetworks::activationFunctionHiddenLayer_;
string  NeuralNetworks::activationFunctionOutputLayer_;
vint	NeuralNetworks::numOfNeuronsInLayersVector_;
bool    NeuralNetworks::useInputDimensionReduction_;
string  NeuralNetworks::dataRepresentation_;
double  NeuralNetworks::dataRepresentationOffset_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

//   Number of Neurons in Hidden Layers in a config file is a string delimited
//   by a column. For example, 5:3:2 means 5, 3, & 2 neurons in the 2nd, 3rd,
//   & 4th layer, respectively. Note the last layer corresponds to the output
//   layer while the first layer is the input layer.
void
NeuralNetworks::configure( Config& configObj, string nnType, int maxEpochs_i )
{
  assert( configObj.get_isConfigured_() );

  srand( time(0) );  // This is for randomize_weights_().

  Error4Cell::configure( maxEpochs_i );

//  activationFunction_         = configObj.get_neuralNetsObj_().get_activationFunction_;
  activationFunctionHiddenLayer_ = configObj.get_neuralNetsObj_().get_activationFunctionHiddenLayer_();
  activationFunctionOutputLayer_ = configObj.get_neuralNetsObj_().get_activationFunctionOutputLayer_();
  activationFunction_            = configObj.get_neuralNetsObj_().get_activationFunction_();
  numOfNeuronsInLayersVector_    = configObj.get_neuralNetsObj_().get_numOfNeuronsInLayersVector_();
  totalNumOfLayers_              = configObj.get_neuralNetsObj_().get_totalNumOfLayers_();
  dataRepresentation_            = configObj.get_dataObj_().get_dataRepresentation_();
  dataRepresentationOffset_      = configObj.get_dataObj_().get_dataRepresentationOffset_();
  assert( ( totalNumOfLayers_>2 ) );  // The minimum is two. Input layer+ output layer+ hidden layer

  if ( nnType == "mcsrn" )
    useInputDimensionReduction_ = true;
  else
    useInputDimensionReduction_ = false;

  Neuron::configure( configObj );  // Notice transfer functions are defined in a Neuron.
}
// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================

NeuralNetworks::NeuralNetworks()
{
}

void
NeuralNetworks::initialize( int inputDataDimension )
{
  assert( ( totalNumOfLayers_ > 2 ) );  // The minimum number of layers is two (input and output).
  assert( !activationFunctionHiddenLayer_.empty() );
  assert( !activationFunctionOutputLayer_.empty() );

  initializeNumOfNodesAndNeurons( inputDataDimension );
  initializeNeurons();
  set_totalNumOfVariableWeights_();
  initialize_weights_();
}

// Many lines in saveInitialWeights() are identical to those in randomize_weights_().
void
NeuralNetworks::saveInitialWeights( int locationX, int locationY )
{
  nout_init << "void Neuron::save_weights_( int neuronIndex )" << endl;
  nout_init << "Cell(" << locationX << "," << locationY << ")" << endl;

  int count = 0;

  // Note the number of neurons at each layer may differ. l stands for layer.
  // This loop will skip the input layer because numOfNeurons_[ 0 ] = 0.
  for ( int l = 1; l < totalNumOfLayers_; l++ )
  {
    nout_init << "  layer=" << l << endl;
    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
    {
      neurons[ count ].randomize_weights_();
      neurons[ count ].save_weights_( count );
      count++;
    }
  }

  // count should be equal to totalNumOfNeurons_
  // Otherwise, array index for neurons does not match totalNumOfNeurons_.
  // Something might have been wrong with the array index count.
  assert( ! ( count - totalNumOfNeurons_ ) );
}

// Note the number of neurons at each layer may differ. l stands for layer.
void
NeuralNetworks::logInitialWeights( int time_o, int time_i, int x, int y, int cellIndex )
{
  lout[ cellIndex] << "\nvoid NeuralNetworks::logInitialWeights( int x, int y )"
                   << " time_o=" << time_o << " time_i=" << time_i << endl;

  int indexForNeuron  = 0;
  int countForWeights = 0;

  do
  {
    countForWeights += neurons[ indexForNeuron ].get_numOfWeights_();
    for ( int m = 0; m < neurons[ indexForNeuron ].get_numOfWeights_(); m++ )
      lout[ cellIndex ] << "  Neurons[" << indexForNeuron << "]::weights[" << m << "] = " << neurons[ indexForNeuron ].get_weights_( m ) << endl;

    indexForNeuron++;
  } while ( indexForNeuron < totalNumOfNeurons_ );

}

int
NeuralNetworks::get_totalNumOfVariableWeights_() const
{
  return totalNumOfVariableWeights_;
}

int
NeuralNetworks::get_totalNumOfNeurons_() const
{
  return totalNumOfNeurons_;
}

int
NeuralNetworks::get_totalNumOfLayers_() const
{
  return totalNumOfLayers_;
}

double
NeuralNetworks::get_error_() const
{
  return error_;
}

vcellerr
NeuralNetworks::get_errors_() const
{
  return errors_;
}

// aBatchOfMlpInputWoBias & MlpOutputVector are
// dummy storages to store input & output data at each layer.
// Because the number of Neurons at each layer differs,
// the size of tmpLayerInput & tmpLayerOutput changes.
// So, vector is prefered to array or pointer.
//
// This function computes Mlp outpus for a set of ALL input data.
// All input data means a matrix of input.
//
//                                <== ii or d
//  jj ************** ... **************      _________________
//  \|/               ...                     |                |
//     ************** ... **************  ==> | NeuralNetworks |
//                    ...                     |________________|
//     ************** ... **************
//
// Important variables for this function are input2DDouble_p_ and
// ouputForOneEpoch_.
// These variables are mxn matrices holding the input samples to NeuralNetworks
// and the corresponding outputs. This function calculates & stores
// the corresponding outputs for the given inputs.
// Then the issue is how the outputs are computed. The outputs are computed
// "column-by-column". In other words, a column input vector for a given ii,
// i.e. aBatchOfMlpInputWoBias, is passed to function
// computeMlpOutput( ... ) and the function "returns" a column output vector
// MlpOutputVector. Well,
// computeMlpOutput( ... ) doesn't actually "return"
// MlpOutputVector, rather MlpOutputVector is
// passed to the function, but in effect, MlpOutputVector is
// considered to be "returned".
//
// computeMlpOutput(
//                   aBatchOfMlpInputWoBias,
//                   MlpOutputVector
//                  );
//   aBatchOfMlpInputWoBias is a vector of an input.
//   This vector can be a scalar if the input takes a scalar form.
//   aBatchOfMlpInputWoBias is an input to function computeMlpOutput
//   ( ... ). MlpOutputVector serves as the "returned" output.
//
// aBatchOfMlpInputWoBias->clear();
// MlpOutputVector->clear();
// aBatchOfMlpInputWoBias can be cleared in computeMlpOutput( ... ), but
// clearning it here makes more sense as it is constructed in this function.
// MlpOutputVector will be cleared in computeMlpOutput( ... ),
// but it's cleared here so that one doesn't have to read computeMlpOutput
// ( ... ).

// The size of aBatchOfVectorInputData is lengthOfABatchOfData X numOfCellInputs where
//   "numOfCellInputs = ( numOfAdjacencies_ + 1 ) * 2;"
// For a 2x2 board, numOfAdjacencies_=2, so numOfCellInputs=6.
// There are two sets of aBatchOfVectorInputData. Both of them are either
// the raw board status or the feedback cell outputs.

vdouble
NeuralNetworks::computeMlpOutputInBatch( int time_o, int time_i, double** aBatchOfVectorInputData, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn )
{
  // Note aVectorOfNeuralNetsOutput is empty in at the beginning.
  // Function computeMlpOutput() will push back the elements.
  vdouble* aVectorOfNeuralNetsInputWoBias  = new vdouble [1];
  vdouble* aVectorOfNeuralNetsOutput       = new vdouble [1];
  vdouble aBatchOfScalarOutputData;

  for ( int d = 0; d < lengthOfABatchOfData; d++ )
  {
    // Design issue: Do not add the bias term here. It will be added
    //   in function computeMlpOutput(...). The bias term is always 1.0,
    //   so it is unnecessary to waste computational resource here.

    if ( useInputDimensionReduction_ )
        aVectorOfNeuralNetsInputWoBias = reduceInputDimension( aBatchOfVectorInputData[d] );
    else
    {
      for ( int jj = 0; jj < numOfCellInputs; jj++ )
        aVectorOfNeuralNetsInputWoBias->push_back( aBatchOfVectorInputData[d][jj] );
    }
    if ( dataRepresentationOffset_ != 0.0 )  // If the offset is zero, why add the offset?
      offsetInputDataRange( aVectorOfNeuralNetsInputWoBias, dataRepresentationOffset_, lengthOfABatchOfData );  // dataRepresentationOffset_ can be 0.0 or 1.0.

    if ( traceOn )
      lout[ cellIndex ] << "Dataset " << d << endl;
    computeMlpOutput( cellIndex, aVectorOfNeuralNetsInputWoBias, aVectorOfNeuralNetsOutput, traceOn );
    assert( ( aVectorOfNeuralNetsOutput->size() == 1 ) );  // DO NOT REMOVE! A cell output needs to be always one while computeMlpOutput can have a multiple output.
    aBatchOfScalarOutputData.push_back( aVectorOfNeuralNetsOutput->at(0) );

    aVectorOfNeuralNetsInputWoBias->clear();
    aVectorOfNeuralNetsOutput->clear();
  }
  return aBatchOfScalarOutputData;
}

// This function is used by double Cell::computeInitialErrors(...), so do not remove.
vdouble
NeuralNetworks::computeMlpOutputInBatch( int time_o, int time_i, double** aBatchOfVectorInputData, Pso pso, int p, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn )
{
  // Note MlpOutputVector is empty in at the beginning.
  // Function computeMlpOutput() will push back the elements.
  vdouble* aBatchOfMlpInputWoBias  = new vdouble [1];
  vdouble* MlpOutputVector       = new vdouble [1];
  vdouble aBatchOfScalarOutputData;

  // First, set the weights in CNN that will be used for computeMlpOutput
  setAParticlePositionAsNnWeights( time_o, time_i, pso.get_weights_( p ), cellIndex, p, traceOn ); //Check here for bug.

  for ( int d = 0; d < lengthOfABatchOfData; d++ )
  {
    // Design issue: Do not add the bias term here. It will be added
    //   in function computeMlpOutput(...). The bias term is always 1.0,
    //   so it is unnecessary to waste computational resource here.

    if ( useInputDimensionReduction_ )
      aBatchOfMlpInputWoBias = reduceInputDimension( aBatchOfVectorInputData[d] );
    else
    {
      for ( int jj = 0; jj < numOfCellInputs; jj++ )
        aBatchOfMlpInputWoBias->push_back( aBatchOfVectorInputData[d][jj] );
    }
    if ( traceOn )
      lout[ cellIndex ] << "Dataset " << d << endl;
    computeMlpOutput( cellIndex, aBatchOfMlpInputWoBias, MlpOutputVector, traceOn );
    assert( ( MlpOutputVector->size() == 1 ) );
    aBatchOfScalarOutputData.push_back( MlpOutputVector->at( 0 ) );

    //aBatchOfCellOutput_[ d ][ p ] = MlpOutputVector->at( 0 );

    aBatchOfMlpInputWoBias->clear();
    MlpOutputVector->clear();
  }

  // aBatchOfScalarOutputData_.size() should be equal to lengthOfABatchOfData.
  assert( !( aBatchOfScalarOutputData.size() - lengthOfABatchOfData ) );

  return aBatchOfScalarOutputData;
}


// Perform feedforward computation for one set of input
// e.g. the first column, second, and so on, respectively.
// Input:  aBatchOfLayerInputWoBias  is a mx1 row vector.
// Output: aBatchOfLayerOutput is a mx1 row vector.
//
// Compute the layer outputs. Note "l" is fixed for all "i"s.
// Note i has nothing to do with m. i is an index for neurons in this
// Mlp structure. When it comes to m or an index for sizeOfInputData_[0],
// the only relevance is to aBatchOfLayerInputWoBias.size() that is equal to sizeOfInputData_[0]
// for the first hidden layer. Other than this layer, aBatchOfLayerInputWoBias.size()
// depends on numOfNeurons_[ l-1 ] for layer l.
//
//    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
//    {
//      tmpOutput = neurons[ count ].compute( aBatchOfLayerInputWoBias, count );
//      aBatchOfLayerOutput->push_back( tmpOutput );
//      count++;
//    }
//
//
// Note aBatchOfLayerInputWoBias for the input layer should include a bias term because
// "neurons[...].compute(...)" calculates the transfer function output of
// the linear-combination of aBatchOfLayerInputWoBias & weights.
//
// Output of this layer is input to the next layer, so
// copy aBatchOfLayerInputWoBias to aBatchOfLayerOutput.
// In order to copy the values, clear all the elements in aBatchOfLayerInputWoBias
// and then assign elements as large as aBatchOfLayerOutput.


// The first aBatchOfLayerInputWoBias is the Mlp Input without the bias term.

void
NeuralNetworks::computeMlpOutput( int cellIndex, vdouble* aBatchOfLayerInputWoBias, vdouble* aBatchOfLayerOutput, bool traceOn )
{
  int      count;        // Index for one dimensional array neurons
  double   tmpOutput;

  count = 0;
  // Note l starts from 1, not 0 because source nodes in the input layer
  // are NOT neurons in a strict sense.
  for ( int l = 1; l < totalNumOfLayers_; l++ )  // l stands for layer.
  {
    aBatchOfLayerOutput->clear();       // Ensure to clear all the elemetns.
    tmpOutput = 0.0;
    if ( traceOn )
      lout[ cellIndex ] << "-layer " << l << endl;
    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
    {
      tmpOutput = neurons[ count ].compute( cellIndex, aBatchOfLayerInputWoBias, count, traceOn );
      aBatchOfLayerOutput->push_back( tmpOutput );
      count++;
    }
    aBatchOfLayerInputWoBias->clear();        // Clear all the elemetns, first.
    aBatchOfLayerInputWoBias->assign( aBatchOfLayerOutput->size(),0 );
    copy( aBatchOfLayerOutput->begin(), aBatchOfLayerOutput->end(), aBatchOfLayerInputWoBias->begin() );
  }
  assert( ! ( count - totalNumOfNeurons_ ) );
  // Note aBatchOfLayerOutput should NOT be cleared at this point
  // because values in the vector should be stored to ouputForOneEpoch_.
}

vdouble
NeuralNetworks::computeMlpOutput( int cellIndex, vdouble aBatchOfLayerInputWoBias, bool traceOn )
{
  int      count;        // Index for one dimensional array neurons
  double   tmpOutput;
  vdouble  layerOutputWoBiasVector;
  vdouble  aBatchOfLayerOutput;

  count = 0;
  // Note l starts from 1, not 0 because source nodes in the input layer
  // are NOT neurons in a strict sense.
  for ( int l = 1; l < totalNumOfLayers_; l++ )  // l stands for layer.
  {
    aBatchOfLayerOutput.clear();       // Ensure to clear all the elemetns.
    tmpOutput = 0.0;
    if ( traceOn )
      lout[ cellIndex ] << "-layer " << l << endl;
    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
    {
      tmpOutput = neurons[ count ].compute( cellIndex, aBatchOfLayerInputWoBias, count, traceOn );
      aBatchOfLayerOutput.push_back( tmpOutput );
      count++;
    }
    aBatchOfLayerInputWoBias.clear();        // Clear all the elemetns, first.
    aBatchOfLayerInputWoBias.assign( aBatchOfLayerOutput.size(),0 );
    copy( aBatchOfLayerOutput.begin(), aBatchOfLayerOutput.end(), aBatchOfLayerInputWoBias.begin() );
  }
  assert( ! ( count - totalNumOfNeurons_ ) );

  return layerOutputWoBiasVector;
}

// TODO: aBatchOfScalarTargetData_ is changed from double* to vdouble. Note this may cause a bug.
double
NeuralNetworks::computeError( vdouble aBatchOfScalarTargetData, vdouble aBatchOfScalarOutputData, int lengthOfABatchOfData, string errorMetric )
{
  assert( !( aBatchOfScalarOutputData.size() - aBatchOfScalarTargetData.size() ));  // Size of both vectors should be equal.
  assert( !( lengthOfABatchOfData - aBatchOfScalarOutputData.size() ) );  // lengthOfABatchOfData should be equal to the size of both vectors.

  double error;
  double sumOfErrors;

  if ( errorMetric == "abs_error")
  {
	sumOfErrors = 0;
    for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      error = abs( aBatchOfScalarTargetData.at(d) - aBatchOfScalarOutputData.at(d) );
      sumOfErrors += error;  // Sum of absolute errors
//***      tout << "   " << "NeuralNetworks::computeError\t" << "|" << aBatchOfScalarTargetData.at(d) << " - " << aBatchOfScalarOutputData.at(d)
//***           << "| = " << error << endl;
    }
  }
  else if ( errorMetric == "mse")
  {
    sumOfErrors = 0;
    for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      error = ( aBatchOfScalarTargetData.at(d)-aBatchOfScalarOutputData.at(d) )
    		 *( aBatchOfScalarTargetData.at(d)-aBatchOfScalarOutputData.at(d) );  // SE (Squared Error)
      sumOfErrors += error;  // Sum of SE
//***      tout << "   " << "NeuralNetworks::computeError\t" << "(" << aBatchOfScalarTargetData.at(d) << " - " << aBatchOfScalarOutputData.at(d)
//***           << ")^2 = " << error << endl;
    }
    sumOfErrors /= lengthOfABatchOfData; // MSE (Mean Squared Error)
  }

  return ( sumOfErrors );
}

// Error vs. cellError?
//   Note the double type variable "error" is not named as cellError, which was the original variable name.
//   During the internal loop, this error is not the cell error, more precisely not yet.
//   The error finally becomes the cell error at the end of the internal loop.
//
// The recurrence part
//   The conventional SRN has the recurrence from the MLP's output.
//   In CSRN, the cell's output is fedback to an MLP's input.
// The simultaneous part
//   The existence of the internal loop characterizes an SRN.
//
// Design issue: How to set terminalConditionNotMetInnerLoop or
//               how to design the inner loop is an issue.
//     The internal loop stops if terminalConditionNotMetInnerLoop=false;
//   Otherwise, it loops through.
//     I'll just use time_i. To do this, just set targetCellError=0.0 to
//   keep the source code as it is. Then the error part will be ignored
//   automatically.

vdouble
NeuralNetworks::runSrnPso( int time_o, double** aBatchOfVectorInputData, vdouble aBatchOfScalarTargetData, Pso& pso, int maxEpochs_i, int numOfCellInputs,
		                   double targetCellError, string errorMetric, int lengthOfABatchOfData, int cellIndex )
{
  bool     terminalConditionNotMetInnerLoop;
  double   error;
  double*  errorForParticles;
  int      time_i;  // epoch for inner lopp
  int      psoNumberOfParticles;
  int      psoSizeOfDomains;
  bool     traceOn  = true;
  bool     traceOff = false;  // For readability. Do not change it to true. Then traceOff technically carries the value for traceOn.
  bool     isTraceon;  // A dummy variable. If this variable is used, we don't know if the trace should be on or off.
  vdouble* aVectorOfNeuralNetsInputWoBias = new vdouble [1];
  vdouble* aVectorOfNeuralNetsOutput      = new vdouble [1];
  vdouble  aBatchOfScalarOutputData;
  vdouble  aBatchOfCurrentOutput;

  psoNumberOfParticles = pso.get_numberOfParticles_();
  psoSizeOfDomains     = pso.get_sizeOfDomains_();
  errorForParticles    = new double [psoNumberOfParticles];

  time_i = maxEpochs_i * time_o;  // A clock for the internal loop or the recurrence part to count time_i consecutively wrt time_o
  terminalConditionNotMetInnerLoop = true;
  while ( terminalConditionNotMetInnerLoop )  // The simultaneous part
  {
    for ( int p = 0; p < psoNumberOfParticles; p++ )
    {
      setAParticlePositionAsNnWeights( time_o, time_i, pso.get_weights_( p ), cellIndex, p, traceOff );  // First, set the weights in CNN that will be used for computeMlpOutput //Check here for bug.
	  aBatchOfScalarOutputData = computeMlpOutputInBatch( time_o, time_i, aBatchOfVectorInputData, lengthOfABatchOfData, numOfCellInputs, cellIndex, traceOff );
	  errorForParticles[p] = computeError( aBatchOfScalarTargetData, aBatchOfScalarOutputData, lengthOfABatchOfData, errorMetric );
    }
    pso.update_pBest( errorForParticles, psoNumberOfParticles );
    pso.update_gBest_( psoNumberOfParticles );
    error = pso.get_globalFitness_();
    errors_.push_back( Error4Cell( time_o, time_i, error ) );  // For logging purposes
    isTraceon = pso.get_is_gBest_updated_();
    aBatchOfCurrentOutput = computeABatchOfScalarOutputFromBestParticle( time_o, time_i, aBatchOfVectorInputData, pso, pso.get_p_gBest_(), lengthOfABatchOfData, numOfCellInputs, cellIndex, isTraceon );

    terminalConditionNotMetInnerLoop = ( time_i<(maxEpochs_i*(time_o+1)-1) ) && ( error>targetCellError ); //  = ( time_i < maxEpochs_i ) && ( error > targetCellError );
    if ( terminalConditionNotMetInnerLoop )
    {
      setFeedbackInputForInternalLoop( aBatchOfVectorInputData, aBatchOfCurrentOutput, lengthOfABatchOfData, numOfCellInputs );  // TODO: Check for a bug here.
      pso.updateVelocityEquation( psoNumberOfParticles, psoSizeOfDomains );
      pso.updatePositionEquation( psoNumberOfParticles, psoSizeOfDomains );
      time_i++;
    }
  }
  error_ = error;
  return aBatchOfCurrentOutput;
//  return error;  // error is actually equal to cellError. Note the cell error is after all the iterations in the internal loop.
}

// runSrnRpso is almost identical to runSrnPso except the part to deal with the history reset feature in the novel PSO algorithm Recurrent PSO (RPSO)
vdouble
NeuralNetworks::runSrnRpso( int time_o, double** aBatchOfVectorInputData, vdouble aBatchOfScalarTargetData, Pso& pso, int maxEpochs_i, int numOfCellInputs,
		                   double targetCellError, string errorMetric, int lengthOfABatchOfData, int cellIndex )
{
  bool     terminalConditionNotMetInnerLoop;
  double   error;
  double*  errorForParticles;
  int      time_i;  // epoch for inner lopp
  int      psoNumberOfParticles;
  int      psoSizeOfDomains;
  bool     traceOn  = true;
  bool     traceOff = false;  // For readability. Do not change it to true. Then traceOff technically carries the value for traceOn.
  bool     isTraceon;  // A dummy variable. If this variable is used, we don't know if the trace should be on or off.
  vdouble* aVectorOfNeuralNetsInputWoBias = new vdouble [1];
  vdouble* aVectorOfNeuralNetsOutput      = new vdouble [1];
  vdouble  aBatchOfScalarOutputData;
  vdouble  aBatchOfCurrentOutput;

  psoNumberOfParticles = pso.get_numberOfParticles_();
  psoSizeOfDomains     = pso.get_sizeOfDomains_();
  errorForParticles    = new double [ psoNumberOfParticles ];

  time_i = maxEpochs_i * time_o;  // A clock for the internal loop or the recurrence part to count time_i consecutively wrt time_o
  terminalConditionNotMetInnerLoop = true;
  while ( terminalConditionNotMetInnerLoop )  // The simultaneous part
  {
    for ( int p = 0; p < psoNumberOfParticles; p++ )
    {
      setAParticlePositionAsNnWeights( time_o, time_i, pso.get_weights_( p ), cellIndex, p, traceOff);  // First, set the weights in CNN that will be used for computeMlpOutput //Check here for bug.
	  aBatchOfScalarOutputData = computeMlpOutputInBatch( time_o, time_i, aBatchOfVectorInputData, lengthOfABatchOfData, numOfCellInputs, cellIndex, traceOff );
	  errorForParticles[p] = computeError( aBatchOfScalarTargetData, aBatchOfScalarOutputData, lengthOfABatchOfData, errorMetric );
    }
    pso.update_pBest( errorForParticles, psoNumberOfParticles );
    pso.update_gBestWtHistoryReset_( psoNumberOfParticles, cellIndex );
    if ( pso.get_is_gBest_updated_() )
      pso.resetParticleHistory( time_o, time_i, psoNumberOfParticles, psoSizeOfDomains, cellIndex );

    error = pso.get_globalFitness_();
    errors_.push_back( Error4Cell( time_o, time_i, error ) );  // For logging purposes
    isTraceon = pso.get_is_gBest_updated_();
    aBatchOfCurrentOutput = computeABatchOfScalarOutputFromBestParticle( time_o, time_i, aBatchOfVectorInputData, pso, pso.get_p_gBest_(), lengthOfABatchOfData, numOfCellInputs, cellIndex, isTraceon );

    if ( isTraceon )
      lout[ cellIndex ] << "\ntime_o=" << time_o << " time_i=" << time_i<< " cellError=" << error << endl;

    terminalConditionNotMetInnerLoop = ( time_i<(maxEpochs_i*(time_o+1)-1) ) && ( error>targetCellError ); //  = ( time_i < maxEpochs_i ) && ( error > targetCellError );
    if ( terminalConditionNotMetInnerLoop )
    {
      setFeedbackInputForInternalLoop( aBatchOfVectorInputData, aBatchOfCurrentOutput, lengthOfABatchOfData, numOfCellInputs );  // TODO: Check for a bug here.
      pso.updateVelocityEquation( psoNumberOfParticles, psoSizeOfDomains );
      pso.updatePositionEquation( psoNumberOfParticles, psoSizeOfDomains );
      time_i++;
    }
  }
  error_ = error;
  return aBatchOfCurrentOutput;
//  return error;  // error is actually equal to cellError. Note the cell error is after all the iterations in the internal loop.
}


// Note the neural network's output should be computed from PSO's best particle.
// For a conventional neural networks, it's less important to output the trained results at each epoch
// because the best particle's location is stored in PSO and the intermediate results are not used.
// However, CNN's intermediate output at each epoch is fedback as an input at the next epoch.
vdouble
NeuralNetworks::computeABatchOfScalarOutputFromBestParticle( int time_o, int time_i, double** aBatchOfVectorInputData, Pso& pso, int indexPsoGBestParticle, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn )
{
  vdouble aBatchOfScalarOutputData;

  setAParticlePositionAsNnWeights( time_o, time_i, pso.get_weights_( indexPsoGBestParticle ), cellIndex, pso.get_p_gBest_(), traceOn );
  aBatchOfScalarOutputData = computeMlpOutputInBatch( time_o, time_i, aBatchOfVectorInputData, lengthOfABatchOfData, numOfCellInputs, cellIndex, traceOn );

  return aBatchOfScalarOutputData;  // This will be stored in aBatchOfCurrentOutput.
}

double
NeuralNetworks::compute_Mse( double** neuralNetsOutputs, double** targets_p )
{
  // TODO: THIS IS TEMPORARY TO REMOVE A COMPILATION ERROR. REMOVE THIS AND MOVE THIS FUNCTION TO CLASS CNN.
  int boardSizeX, boardSizeY;
  boardSizeX = 2;
  boardSizeY = 2;
  // TODO: THIS IS TEMPORARY TO REMOVE A COMPILATION ERROR. REMOVE THIS AND MOVE THIS FUNCTION TO CLASS CNN.

  assert( ( boardSizeX > 0 ) && ( boardSizeY > 0 ) );

  // Do we need to assert neuralNetsOutputs here? If so, how?
  double tmpError;
  double tmpSquaredError; // Square Error
  double tmpSumOfSes;     // Sum of Square Errors
  double tmpMse;          // Mean Square Error

  tmpSumOfSes = 0.0;
  tout << "  (x,y):\tsumOfSEs\tError^2\tError = target - NNsOutput" << endl;

  for ( int x = 0; x < boardSizeX; x++ )
  {
    for ( int y = 0; y < boardSizeY; y++ )
    {
      tmpError        = targets_p[ x ][ y ] - neuralNetsOutputs[ x ][ y ];
      tmpSquaredError = tmpError * tmpError;
      tmpSumOfSes    += tmpSquaredError;

      tout << "  (" << x << "," << y << "):\t"
           << tmpSumOfSes << "\t"
           << tmpSquaredError << "\t"
           << tmpError << " = " << targets_p[ x ][ y ]
           << " - " << neuralNetsOutputs[ x ][ y ] << endl;
    }
  }
//  tmpMse = tmpSumOfSes / static_cast<double> ( totalNumOfTargetData_ );  // TODO: Chage this when this function is actually used.
// Note "totalNumOfTargetData_ = boardSizeX * boardSizeY * lengthOfABatchOfData_;"

  tout << "  MSE: " << tmpMse << " = " << tmpSumOfSes << " / ";

  return tmpMse;
}

vdouble
NeuralNetworks::runMlpPso( int lengthOfABatchOfData )
{
  double  cellError;
  int     psoNumberOfParticles;
  int     psoSizeOfDomains;
  vdouble aBatchOfCurrentOutput;
  double  error;
/*
   // Moved from Cell.{*pp} from here. TODO: Eventually remove these variables.
  double* outputData_ = new double [ lengthOfABatchOfData ];
  double* mse_        = new double [ psoNumberOfParticles ];  // TODO: Eventually this variable should be replaced by an existing variable.
  // Moved from Cell.{*pp} from here. TODO: Eventually remove these variables.

  psoNumberOfParticles = pso_.get_numberOfParticles_();
  psoSizeOfDomains  = pso_.get_sizeOfDomains_();

  time_i_ = time_o_;
  for ( int p = 0; p < psoNumberOfParticles; p++ )
  {
	aBatchOfScalarOutputData_ =  nns_.computeMlpOutputInBatch( aBatchOfVectorInputData_, pso_, p, lengthOfABatchOfData, numOfCellInputs_ );
    mse_[ p ] = computeMseInBatch( p, lengthOfABatchOfData );
    cerr << "  mse[" << p << "]=" << mse_[ p ] << " ";
  }
  cerr << endl;
  pso_.evaluate( time_i_, mse_, psoNumberOfParticles );
  cellError = pso_.get_globalFitness_();

  // Even if both values are displayed the same, e.g. cellError = 0.000000 &
  // targetCellError_ = 0.000000, the actual value in cellError may be larger
  // than zero, e.g. 0.00000001.
  if ( cellError > targetCellError_ )
  {
	  pso_.updateVelocityEquation( psoNumberOfParticles, psoSizeOfDomains );
	  pso_.updatePositionEquation( psoNumberOfParticles, psoSizeOfDomains );
  }
  else  isHibernate_ = true;

  cellError_ = cellError;
*/
  error_ = error;
  return aBatchOfCurrentOutput;
}

vdouble
NeuralNetworks::runPsrnPso( int lengthOfABatchOfData )
{
  bool    terminalConditionNotMetInnerLoop;
  double  cellError;
  int     psoNumberOfParticles;
  int     psoSizeOfDomains;
  vdouble aBatchOfCurrentOutput;
  double  error;

/*
   // Moved from Cell.{*pp} from here. TODO: Eventually remove these variables.
  double* outputData_ = new double [ lengthOfABatchOfData ];
  double* mse_        = new double [ psoNumberOfParticles ];  // TODO: Eventually this variable should be replaced by an existing variable.
  // Moved from Cell.{*pp} from here. TODO: Eventually remove these variables.

  psoNumberOfParticles = pso_.get_numberOfParticles_();
  psoSizeOfDomains     = pso_.get_sizeOfDomains_();

  // If true, next loop; o.w., loop is over.
  terminalConditionNotMetInnerLoop = true;
  time_i_ = 0;
  time_i_ += maxEpochs_i_ * time_o_;  // to count time_i consecutively.
  cellError  = numeric_limits<double>::max();

  while ( terminalConditionNotMetInnerLoop )
  {
    for ( int p = 0; p < psoNumberOfParticles; p++ )
    {
      aBatchOfScalarOutputData_ = nns_.computeMlpOutputInBatch( aBatchOfVectorInputData_, pso_, p, lengthOfABatchOfData, numOfCellInputs_ );
      mse_[ p ] = computeMseInBatch( p, lengthOfABatchOfData );
    }
    pso_.evaluate( time_i_, mse_, psoNumberOfParticles );
    cellError = pso_.get_globalFitness_();
    terminalConditionNotMetInnerLoop
      = ( time_i_ < ( maxEpochs_i_ * ( time_o_ + 1 ) - 1 ) )
          &&
        ( cellError > targetCellError_ );
//    = ( time_i_ < maxEpochs_i_ ) && ( cellError > targetCellError_ );

    // Store the output.
    for ( int d = 0; d < lengthOfABatchOfData; d++ )
    {
      outputData_[ d ]
        = aBatchOfCellOutput_[ d ][ pso_.get_p_gBest_() ];
    }

    if ( terminalConditionNotMetInnerLoop )
    {
      // Feedback input!!!
      for ( int d = 0; d < lengthOfABatchOfData; d++ )
      {
        aBatchOfVectorInputData_[d][ numOfCellInputs_ - 1 ] = outputData_[ d ];
      }
      pso_.updateVelocityEquation( psoNumberOfParticles, psoSizeOfDomains );
      pso_.updatePositionEquation( psoNumberOfParticles, psoSizeOfDomains );

      time_i_++;
    }
  }
  if ( cellError <= targetCellError_ )  isHibernate_ = true;
  cellError_ = cellError;
*/
  error_ = error;

  return aBatchOfCurrentOutput;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

// Note the nodes in the input layer are NOT neurons. They are just source nodes.
//
// Note the number Of nodes is not equal to the number of neurons.
// Well, nodes in the input layer are NOT Neurons, so they make things
// a little bit more complicated.
// First, two distinct terms to refer to node & neuron.
// Second, fixedWeights & variableWeights refer to weights
//   for node & neuron, respectively.
// Why a variable weight? The weights are changed while a fixed weight of
// an input node is fixed to 1 all the time during training.

// numOfNodes_ = numOfNeurons_ + source nodes in the input layer.
// This may be confusing, but important!
// The source nodes that interface input data are NOT neurons.
//
// An array numOfNeurons_ stores the number of neurons in each layer.
// Similarly,
// an array numOfNodes_ stores the number of nodes in each layer.
// For example, 2x5x1 network
//   totalNumOfLayers_ = 3;
//   numOfNeurons_[0] = 0; numOfNodes_[0]=2;
//   numOfNeurons_[1] = 5; numOfNodes_[1]=5;
//   numOfNeurons_[2] = 1; numOfNodes_[2]=1;
// Notice numOfNeurons_ is obsolete and no longer in use.
// It is presented in this example to show the conceptual difference between
// a neuron and a node.

void
NeuralNetworks::initializeNumOfNodesAndNeurons( int inputDataDimension )
{
  assert( numOfNeuronsInLayersVector_.size() );
  assert( ( totalNumOfLayers_ > 2 ) );  // The minimum number of layers is two (input and output).

  int numOfNodes;
  int numOfNeurons;

  numOfNodes_   = new int [totalNumOfLayers_];
  numOfNeurons_ = new int [totalNumOfLayers_];

  totalNumOfNeurons_ = 0;
  for ( int l = 0; l < totalNumOfLayers_; l++ )
  {
    if ( l == 0 )
    {
      numOfNeurons = 0;
      numOfNodes   = inputDataDimension + 1; // +1 is for the bias term
    }
    else
    {
      numOfNeurons = numOfNeuronsInLayersVector_.at( l-1 );
      numOfNodes   = numOfNeurons + 1;  // +1 is for the bias term
    }
    totalNumOfNeurons_ += numOfNeurons;
    numOfNodes_[ l ]    = numOfNodes;
    numOfNeurons_[ l ]  = numOfNeurons;
  }
  is_numOfNodes_set_ = true;
}

// Comment on design issues:
//   The size of Neural Networks is prefixed during the simulations,
//   so use of pointer is fine. In other words, vector object is unnecessary.
//
// This function constructs one dimensional pointer neurons.
// Originally, 2D pointer nrn was used, but 1D pointer turned out to be
// easier to code considering Cellular Neural Networks structure.
// Mapping the weights in the training algorithm can be tricky, so use 1D pointer.
//
// This function sets Neuron::num_inputs_ for all instantiated neurons.
// Assume instances of class Neuron, neurons, have been already constructed.
//
// Be careful not to confuse a node with a neuron.
// A node is a superset of a neuron.
// In the input layer, there exists nodes, not neurons.
// For example, a 2x5x1 network has 8 (=2+5+1) nodes and 6 (=5+1) neurons .
//
//   Note the number of neurons at each layer may differ.
// l stands for layer. i is an index for a neuron in the given layer.
// The for loop starts from l=1 because the first/input layer does not have
// neurons.
//   A node is a superset of a neuron. A neuron is a special node with
// a computational ability. A conventional artificial neuron has two components:
// a linear combination of the neuron inputs and activation function. A node
// without the computational ability is used as a point to draw the


void
NeuralNetworks::initializeNeurons()
{
  assert( ( totalNumOfNeurons_ > 0 ) );

  int numOfInputsToANeuron;
  int count (0);

  neurons = new Neuron [ totalNumOfNeurons_ ];

  // Note this nested loop skips the input layer because numOfNeurons_[0]=0.
  for ( int l = 1; l < totalNumOfLayers_; l++ )
  {
    numOfInputsToANeuron = numOfNodes_[ l-1 ];
    for ( int i = 0; i < numOfNeurons_[l]; i++ )
    {
      // A source node takes only single input.
      // Except the first/input layer, the number of inputs to this node is
      // the number of nodes at the previous layer.
      initializeANeuron( numOfInputsToANeuron, count, l );
      count++;  // count is an index of a neuron.
    }
  }
  assert( ! ( count - totalNumOfNeurons_ ) );  // At the end of the loop, count should be equal to totalNumOfNeurons_
                                               // Otherwise, array index for neurons does not match totalNumOfNeurons_.
}

// Initialize a neuron.
// In essence, all the following lines are
//
//   neurons[ indexNeuron ].initialize( numOfInputsToANeuron, numInputsToANeuron, l, TANSIG );
//
// with different option for the transfer function.
// All the neurons on output layer have linear transfer function.

void
NeuralNetworks::initializeANeuron( int numInputsToANeuron, int indexNeuron, int indexLayer )
{
  // The activation functions except the output layer are set to TANSIG
  if (  indexLayer != totalNumOfLayers_ - 1 )  // Hidden layer
  {
    neurons[ indexNeuron ].initialize( numInputsToANeuron, indexLayer, activationFunctionHiddenLayer_ );
  }
  // The activation function of the output layer is set to LINEAR
  else if (  indexLayer == totalNumOfLayers_ - 1 )  // Output layer
  {
    neurons[ indexNeuron ].initialize( numInputsToANeuron, indexLayer, activationFunctionOutputLayer_ );
  }
}

// Calculate totalNumOfVariableWeights_ to update weights by population-based
// training algorithm. The weights in the input layer should not be counted
// because the value is fixed to 1.
//
// For example, a 1x5x1 network has "totalNumOfVariableWeights_ = 16"
// because 16 = (1+1)*5 + (5+1)*1. Don't forget each neuron has an additional
// weight for a bias term.

void
NeuralNetworks::set_totalNumOfVariableWeights_()
{
  assert( is_numOfNodes_set_ );

  totalNumOfVariableWeights_ = 0;
  for ( int l = 0; l < totalNumOfLayers_; l++ )
  {
    if ( l != 0 )
    {
      totalNumOfVariableWeights_
        += numOfNodes_[ l-1 ]  * numOfNeurons_[ l ];
        //+= ( numOfNodes_[ l-1 ] + 1 ) * numOfNodes_[ l ];
    }
  }
}

void
NeuralNetworks::initialize_weights_()
{
  if ( initialWeightsMode_ == "random" )
    randomize_weights_();
  else if ( initialWeightsMode_ == "load_manually" )
    load_weights_();
}

// Weights of the input layer neurons are set to 1.
// Those of other layers are randomized.
void
NeuralNetworks::randomize_weights_()
{
  int count = 0;

  // Note the number of neurons at each layer may differ. l stands for layer.
  // This loop will skip the input layer because numOfNeurons_[ 0 ] = 0.
  for ( int l = 1; l < totalNumOfLayers_; l++ )
    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
    {
      neurons[ count ].randomize_weights_();
      count++;
    }

  // count should be equal to totalNumOfNeurons_
  // Otherwise, array index for neurons does not match totalNumOfNeurons_.
  // Something might have been wrong with the array index count.
  assert( ! ( count - totalNumOfNeurons_ ) );
}

void
NeuralNetworks::load_weights_()
{
  int count;

  // Skip the very first two lines. Both lines should include:
  // n	(x,y)	[l,i]	neurons[count].save_weights_();
  //
  // Note the above line is a new line.
  char str[ 255 ];
  nin_init.getline( str, 255 );  // Delim defaults to '\n'

  // This loop will skip the input layer because numOfNeurons_[ 0 ] = 0.
  // Note the number of neurons at each layer may differ.
  // l stands for layer.
  count = 0;
  for ( int l = 1; l < totalNumOfLayers_; l++ )
  {
    for ( int i = 0; i < numOfNeurons_[ l ]; i++ )
    {
      nout_init << "void NeuralNetworks::load_weights_()\t" << "neurons[" << count << "].load_weights_();" << endl;
      neurons[ count ].load_weights_( count );
      count++;
    }
  }

  // count should be equal to totalNumOfNeurons_
  // Otherwise, array index for neurons does not match totalNumOfNeurons_.
  // Something might have been wrong with the array index count.
  assert( ! ( count - totalNumOfNeurons_ ) );
}

// The current neural network output is looped back as the input to the neural network. Note the location of the feedback input is fixed.
void
NeuralNetworks::setFeedbackInputForInternalLoop( double** aBatchOfVectorInputData, vdouble aBatchOfCurrentOutput, int lengthOfABatchOfData, int numOfCellInputs )
{
  // Feedback input!!!
  for ( int d = 0; d < lengthOfABatchOfData; d++ )
    aBatchOfVectorInputData[d][ numOfCellInputs - 1 ] = aBatchOfCurrentOutput[ d ];
}

// Two sets of ternary digits are converted to decimal numbers: raw data and cell outputs.
//
// inputData is a one dimensional vector that corresponds to a single data from
// a matrix aBatchOfVectorInputData. inputData = aBatchOfVectorInputData[d] where the matrix aBatchOfVectorInputData
// has aBatchOfVectorInputData[d][jj].
//
// The 222(3)=3^3-1=27-1=26

vdouble*
NeuralNetworks::reduceInputDimension( double* aVectorOfInputData )
{
  double decimalNumber;
  double mlpInput;
  vdouble* aVectorOfMlpInputData = new vdouble [1];

  // Assume 2x2. Then numOfCellInputs = 6;
  // Two sets of ternary digits (a set of scalar inputs and a set of cell outputs)
  // are converted to the corresponding decimal numbers.
  decimalNumber = numberConversionObj_.ter2dec( aVectorOfInputData[0], aVectorOfInputData[1], aVectorOfInputData[2] );
  mlpInput = decimalNumber / 26.0;  // Normalize the values. The maximum number for three digits of ternary number is 26.0.
  aVectorOfMlpInputData->push_back( mlpInput );

//***  tout << aVectorOfInputData[0] << " " << aVectorOfInputData[1] << " " << aVectorOfInputData[2]
//***       << " => " << decimalNumber << "/26 = " << mlpInput << endl;

  decimalNumber = numberConversionObj_.ter2dec( aVectorOfInputData[3], aVectorOfInputData[4], aVectorOfInputData[5] );
  mlpInput = decimalNumber / 26.0;  // Normalize the values
  aVectorOfMlpInputData->push_back( mlpInput );

//***  tout << aVectorOfInputData[3] << " " << aVectorOfInputData[4] << " " << aVectorOfInputData[5]
//***	   << " => " << decimalNumber << "/26 = " << mlpInput << endl;

//***  tout << "aVectorOfMlpInputData[0]=" << aVectorOfMlpInputData->at( 0 ) << "\t"
//***	   << "aVectorOfMlpInputData[1]=" << aVectorOfMlpInputData->at( 1 ) << endl;

  return aVectorOfMlpInputData;
}

void
NeuralNetworks::setAParticlePositionAsNnWeights( int time_o, int time_i, double* weights, int cellIndex, int psoIndex, bool traceOn )
{
  int indexForNeuron;
  int countForWeights;

  indexForNeuron  = 0;
  countForWeights = 0;

  if ( traceOn )
  {
	lout[ cellIndex ] << "\nvoid NeuralNetworks::setAParticlePositionAsNnWeights( double* weights )"
	                  << " time_o=" << time_o << " time_i=" << time_i << " psoIndex=" << psoIndex << endl;
  }

  do
  {
    neurons[ indexForNeuron ].set_weights_( weights, countForWeights );
    countForWeights += neurons[ indexForNeuron ].get_numOfWeights_();

    if ( traceOn )
    {
      for ( int m = 0; m < neurons[ indexForNeuron ].get_numOfWeights_(); m++ )
        lout[ cellIndex ] << "  Neurons[" << indexForNeuron << "]::weights[" << m << "] = " << neurons[ indexForNeuron ].get_weights_( m ) << endl;
    }

    indexForNeuron++;
  } while ( indexForNeuron < totalNumOfNeurons_ );
  // Put indexForNeuron++ inside the do-while loop for better readability.
}

// assert( ( dataRepresentationOffset != 0.0 ));
//   If the offset value is zero, why do you need to call this function?
//   Just add an if statement to skip this function!

void
NeuralNetworks::offsetInputDataRange( vdouble* aVectorOfNeuralNetsInputWoBias, int dataRepresentationOffset, int lengthOfABatchOfData )
{
  assert( ( dataRepresentationOffset != 0.0 ));
  assert( ( aVectorOfNeuralNetsInputWoBias->size() != 0 ) );

  int size = aVectorOfNeuralNetsInputWoBias->size();

  for ( int d = 0; d < size; d++ )
  {
	tout << "   " << "NeuralNetworks::offsetInputDataRange()\t" << aVectorOfNeuralNetsInputWoBias->at(d) << "+" << dataRepresentationOffset;
    aVectorOfNeuralNetsInputWoBias->at(d) += dataRepresentationOffset;  // dataRepresentationOffset is meant to add 1.0.
    tout << "=" << aVectorOfNeuralNetsInputWoBias->at(d) << endl;
  }
}
