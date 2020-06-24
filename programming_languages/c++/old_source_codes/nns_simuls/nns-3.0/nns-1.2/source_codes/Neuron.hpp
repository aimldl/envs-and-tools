#ifndef  __NEURON_HPP_
#define  __NEURON_HPP_

#include  "SimObject.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      Neuron: public SimObject
{
public:
           Neuron();
           Neuron( string mode );
          ~Neuron();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  void     initialize( int numOfInputs, int layerIndex, string activationFn );
  void     assign_weights_( double* weights );
  void     randomize_weights_();
  void     test_moduloThreeFunction( double from, double incr, double to );
  int      get_numOfInputs_() const;
  int      get_layerIndex_() const;
  int      get_numOfWeights_() const;
  double   get_weights_( int w ) const;
  void     set_weights_( double* weights, int pointerFrom );
  double   compute( int cellIndex, const vdouble* inputVectorWoBias, int neuronIndex, bool traceOn );
  double   compute( int cellIndex, const vdouble inputVectorWoBias, int neuronIndex, bool traceOn );
  void     save_weights_( int neuronIndex );
  void     load_weights_( int neuronIndex );
  void     fetch_weights_( vdouble* weights_vector_p );

private:
  double   doLinearCombinationWtBias( int cellIndex, const vdouble* tmpInputVectorWoBias, double* weights, bool traceOn );
  double   doLinearCombinationWtBias( int cellIndex, const vdouble tmpInputVectorWoBias, double* weights, bool traceOn );
  double   activationFunction( int cellIndex, double input, bool traceOn );
  double   logsigFunction( double input );
  double   tansigFunction( double input );
  double   ternaryStepFunction( double input, double c, double w );
  double   moduloThreeFunction( double input );

  static
  double   slopeParameterTansig_;    // For tansigFunction.
  static
  double   slopeParameterLogsig_;    // For logsigFunction.
  static
  double   w_;                 // Width of the 2nd step
  static
  double   c_;                 // Center of the 2nd step.
  static
  string   mode_;

  int      layerIndex_;
  int      numOfInputs_;       // Number of inputs are equal to number of synaptic weights.
  int      numOfWeights_;
  double*  inputs_;            // Input signals, bias is included to inputs_
  double*  weights_;           // Synaptic weights
  double   output_;            // There is a single value for a Neuron output.
  string   activationFn_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// It used to be "class      Neuron:". I believe inheriting SimObject should be
// fine. I inherit SimObject just to use log_data_. Neuron can be a base class
// by itself. I'm not sure if this is an overkill to inherit SimObject.
//
// PARAMETERS FOR TERNARY STEP FUNCTION
//          <--- w ---> -----------
//          ------------|
//  --------|
//
//        c-w/2  c   c+w/2
//
// string   activationFn_;
//   This is NOT static because activation function for each layer may be
//   different. For example, the output layer neurons may be set to LINEAR.
//
// double*  inputs_;
//   Input signals, bias is included to inputs_
// double*  weights_;
//   Synaptic weights should be fixed to 1.0 for the input layer
//   In other layers, weights will vary during the training.
//
// double   output_;
//   There is a single value for a Neuron output. A Neural Networks has multiple outputs.
// output_ = activationFunction( linearCombination )
//
// int      numOfInputs_;
//   Number of inputs are equal to number of synaptic weights. Here we consider
// a Cellular Neural Networks with the size neurons, so declare num_inputs as static.
