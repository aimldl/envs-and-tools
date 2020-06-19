#ifndef  __NEURALNETWORK_HPP_
#define  __NEURALNETWORK_HPP_

#include   <ctime>    // For time(...).

#include  "Error.hpp"
#include  "SimObject.hpp"
#include  "Neuron.hpp"
#include  "Pso.hpp"
#include  "NumberConversion.hpp"

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<Error4Cell> vcellerr;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      NeuralNetworks: public SimObject
{
public:
           NeuralNetworks();
  static
  void     configure( Config& configObj, string nnType, int maxEpochs_i );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  void     initialize( int inputDataDimension );
  void     saveInitialWeights( int locationX, int locationY );
  void     logInitialWeights( int time_o, int time_i, int x, int y, int cellIndex );
  int      get_totalNumOfVariableWeights_() const;
  int      get_totalNumOfNeurons_() const;
  int      get_totalNumOfLayers_() const;
  double   get_error_() const;
  vcellerr get_errors_() const;

  vdouble  computeMlpOutputInBatch( int time_o, int time_i, double** aBatchOfVectorInputData, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn );
  vdouble  computeMlpOutputInBatch( int time_o, int time_i, double** aBatchOfVectorInputData, Pso pso, int p, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn );
  void     computeMlpOutput( int cellIndex, vdouble* layerInputWoBiasVector, vdouble* layerOutputWoBiasVector, bool traceOn );
  vdouble  computeMlpOutput( int cellIndex, vdouble layerInputWoBiasVector, bool traceOn );

  double   computeError( vdouble aBatchOfScalarTargetData, vdouble aBatchOfScalarOutputData, int lengthOfABatchOfData, string errorMetric );
  vdouble  runSrnPso( int time_o, double** aBatchOfVectorInputData, vdouble aBatchOfScalarTargetData, Pso& pso, int maxEpochs_i, int numOfCellInputs, double targetCellError, string errorMetric, int lengthOfABatchOfData, int cellIndex );
  vdouble  runSrnRpso( int time_o, double** aBatchOfVectorInputData, vdouble aBatchOfScalarTargetData, Pso& pso, int maxEpochs_i, int numOfCellInputs, double targetCellError, string errorMetric, int lengthOfABatchOfData, int cellIndex );
  vdouble  computeABatchOfScalarOutputFromBestParticle( int time_o, int time_i, double** aBatchOfVectorInputData, Pso& pso, int indexPsoGBestParticle, int lengthOfABatchOfData, int numOfCellInputs, int cellIndex, bool traceOn );
  double   compute_Mse( double** neuralNetsOutputs, double** targets_p );

  vdouble  runMlpPso( int lengthOfABatchOfData );
  vdouble  runPsrnPso( int lengthOfABatchOfData );

  Neuron*  neurons;
  int*     numOfNeurons_;

  int      epoch_;  // These variables were in a function in class Mlp, but moved here.
  int      numOfPsoParticles_;  // This variable is for PSO training algorithm.

protected:
  static
  int      activationFunction_;
  static
  vint     numOfNeuronsInLayersVector_;

  int*     numOfNodes_;

private:
  void     initializeNumOfNodesAndNeurons( int inputDataDimension );
  void     initializeNeurons();
  void     initializeANeuron( int numInputsToANeuron, int indexNeuron, int indexLayer );
  void     set_totalNumOfVariableWeights_();
  void     initialize_weights_();
  void     randomize_weights_();
  void     load_weights_();
  void     setFeedbackInputForInternalLoop( double** aBatchOfVectorInputData, vdouble aBatchOfCurrentOutput, int lengthOfABatchOfData, int numOfCellInputs );

  vdouble* reduceInputDimension( double* aVectorOfInputData );
  void     setAParticlePositionAsNnWeights( int time_o, int time_i, double* weights, int cellIndex, int psoIndex, bool traceOn );
  void     offsetInputDataRange( vdouble* aVectorOfNeuralNetsInputWoBias, int dataRepresentationOffset, int lengthOfABatchOfData );

  static
  string   activationFunctionHiddenLayer_;
  static
  string   activationFunctionOutputLayer_;
  static
  int      totalNumOfNeurons_;
  static
  int      totalNumOfLayers_;
  static
  string   dataRepresentation_;
  static
  double   dataRepresentationOffset_;
  static
  bool     useInputDimensionReduction_;  // Design issue: Clearly, this feature is responsible by a neural networks, not cnn.
                                         //  cnn doesn't care if neural networks reduce the input dimension or not.
                                         //  cnn cares about the cnn structure, neighborhood connectivity. etc.
  NumberConversion
           numberConversionObj_;
  int      totalNumOfVariableWeights_;
  bool     is_numOfNodes_set_;
  double   error_;
  vcellerr errors_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// REFERENCE
//   Simon Haykin, "Neural Networks: A comprehensive Foundation",
//                  Second edition, Person Education, 1999.
//   You may refer to:
//                  4.2. Some Preliminaries, page 159.
// REFERENCE
//
// "NeuralNetworks" is a set of "Neuron"s.
//
// Note inputs_ & targets_ point class Inputs, which points to actual values.
// For example,
//
//   class actualData::inputs_ <- class Inputs::inputs_ <- class NeuralNetworks::inputs_p_
//
// Why class Inputs is necessary?
//   The class exists to provide the same interface to class NeuralNetworks.
//   Class NeuralNetworks may take various types of inputs.
//   With the use of class Inputs, Class NeuralNetworks can always point class
//   Inputs, which takes care of the interfacing issue with different types.
//
// THIS IS A COPY FROM CLASS INPUTS. THIS IS A COPY FROM CLASS INPUTS.
//
// Example 1 ) A scalar input/output
//   a scalar input ( 1xn )                 a scalar output ( 1xn )
//
//   ****** ... ****** ==> NeuralNetworks ==> ****** ... ******
//
//            size of this input/output = [1, n]
//     length of an input/output sample = 1
//   length of the input/output samples = n
//
// Example 2 ) A vector input/output
//   a vector input ( mxn )                 a vector output ( mxn )
//
//   ****** ... ******                        ****** ... ******
//     ...       ...                           ...        ...
//   ****** ... ****** ==> NeuralNetworks ==> ****** ... ******
//     ...       ...                           ...        ...
//   ****** ... ******                       ****** ... ******
//
//            size of this input/output = [m, n]  size of a matrix
//     length of an input/output sample = m       length of a column vector
//   length of the input/output samples = n       length of a row vector
//
// THIS IS A COPY FROM CLASS INPUTS. THIS IS A COPY FROM CLASS INPUTS.

// Number of Hidden layers exclude the input layer and output layer.
