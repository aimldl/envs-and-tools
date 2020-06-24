#include  "Neuron.hpp"

// Definition of static variables
double	Neuron::slopeParameterTansig_;
double	Neuron::slopeParameterLogsig_;
double	Neuron::w_;
double	Neuron::c_;
string	Neuron::mode_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!
void
Neuron::configure( Config& configObj )
{
  assert( configObj.get_isConfigured_() );

  slopeParameterLogsig_ = configObj.get_neuralNetsObj_().get_slopeParamLogsig_();
  slopeParameterTansig_ = configObj.get_neuralNetsObj_().get_slopeParamTansig_();
  w_                    = configObj.get_neuralNetsObj_().get_ternaryStepFn_w_();
  c_                    = configObj.get_neuralNetsObj_().get_ternaryStepFn_c_();
}
// IMPORTANT! RUN THIS FUNCTION BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================

Neuron::Neuron()
{
  assert( slopeParameterLogsig_ );
  assert( slopeParameterTansig_ );

  activationFn_ = "none";
}

Neuron::Neuron( string mode )
{
  mode_ = mode;
  if ( mode_ == "test" )
    cout << "Class Neuron is in a test mode." << endl;
}

Neuron::~Neuron()
{
  delete[] inputs_;
  delete[] weights_;
}

void
Neuron::initialize( int numOfInputs, int layerIndex, string activationFn )
{
  numOfInputs_  = numOfInputs;
  numOfWeights_ = numOfInputs;
  layerIndex_   = layerIndex;
  activationFn_ = activationFn;

  if ( activationFn == "ternary_step" )  // Both c_ and w_ need to be set. Assert only w_ because c_=0 is a possibility.
    assert( ( w_ > 0 ));

  assert( numOfInputs_ );   // numOfInputs_  must not be zero.
  inputs_  = new double [ numOfInputs_ ];

  assert( numOfWeights_ );  // numOfWeights_ must not be zero.
  weights_ = new double [ numOfWeights_ ];
}

void
Neuron::assign_weights_( double* weights )
{
  for ( int i = 0; i < numOfWeights_; i++ )
    weights_[i] = weights[i];
}

void
Neuron::save_weights_( int neuronIndex )
{
  nout_init << "  neuronIndex=" << neuronIndex << ": ";
  for ( int i = 0; i < numOfWeights_; i++ )
    nout_init << weights_[i] << " ";
  nout_init << endl;
}

void
Neuron::load_weights_( int neuronIndex )
{
  tout << "\nvoid Neuron::load_weights_( int neuronIndex )" << " neuronIndex=" << neuronIndex << endl;
  char str[ 255 ];

  // A line should look like "0	(0,0)	[1,0]   0.450367 0.704932 0.895424".
  // Skip the first three columns because those values correspond to "n	(x,y)	[l,i]".
  // For example, "0	(0,0)	[1,0]" should be skipped.
  // Note a tab and a space are automatically ignore if ">>" is used.

  for ( int j = 0; j < 3; j++ )
  {
	  nin_init >> str;
	  tout << "str=" << str << endl;
  }

  for ( int i = 0; i < numOfWeights_; i++ )
  {
	nin_init >> str;
    weights_[i] = atof( str );
    tout << "str=" << str << "\tweights_[" << i << "]=" << weights_[i] << endl;
  }
}

void
Neuron::fetch_weights_( vdouble* weights_vector_p )
{
  weights_vector_p->clear();
  for ( int i = 0; i < numOfWeights_; i++ )
    weights_vector_p->push_back( weights_[i] );
}

void
Neuron::randomize_weights_()
{
  for ( int i = 0; i < numOfWeights_; i++ )
    weights_[i] = static_cast<double> ( random() ) / static_cast<double> ( RAND_MAX );
}

void
Neuron::test_moduloThreeFunction( double from, double incr, double to )
{
  double input;
  double output;

  cout << "input\toutput" << endl;
  for ( input = from; input < to; input+=incr )
  {
    output = moduloThreeFunction( input );
    cout << input << "\t" << output << endl;
  }
}

int
Neuron::get_layerIndex_() const
{
  return layerIndex_;
}

int
Neuron::get_numOfWeights_() const
{
  return numOfWeights_;
}

int
Neuron::get_numOfInputs_() const
{
  return numOfInputs_;
}

double
Neuron::get_weights_( int w ) const
{
  return weights_[ w ];
}

// Maybe it's risky to use a pointer to weights_, but it will run faster.
// Just be careful of the number of inputs & weights.
void
Neuron::set_weights_( double* weights, int pointerFrom )
{
  weights_ = weights + pointerFrom;
//  for ( int m = pointerFrom; m < ( pointerFrom + numOfWeights_ ); m++ )
//    nout << "    weights[" << m << "] = " << weights[m] << endl;
}

// double Neuron::compute( const vdouble* inputVectorWoBias )
//   Assume the bias term is included in inputVectorWoBias.
//   Therefore, numOfInputs_ == inputVectorWoBias->size() == numOfCellInputs_+1;
// inputVectorWoBias.size() should be equal to numOfInputs_.
// Note Neuron::numOfInputs_
//    = Inputs::sizeOfInputData_[0]
//    = NeuralNetworks::sizeOfInputData_[0]
// Recall NeuralNetworks::sizeOfInputData_[0] is "naturally" equal to
//   Inputs::sizeOfInputData_[0] because NeuralNetworks::sizeOfInputData_[0]
//   is set to Inputs::sizeOfInputData_[0].
//
// If you see an assertion error for the following line, it is suggested to
// double-check inputVectorWoBias and the existence of a bias term in it.

double
Neuron::compute( int cellIndex, const vdouble* inputVectorWoBias, int neuronIndex, bool traceOn )
{
  if ( traceOn )
    lout[ cellIndex ] << " Neuron[" << neuronIndex << "] ";

  assert( ! ( numOfInputs_ -1 - inputVectorWoBias->size() ) );  // -1 because the bias term is lack.

  double tmpOutput;

  tmpOutput = doLinearCombinationWtBias( cellIndex, inputVectorWoBias, weights_, traceOn );
  output_   = activationFunction( cellIndex, tmpOutput, traceOn );

  return    output_;
}

double
Neuron::compute( int cellIndex, const vdouble inputVectorWoBias, int neuronIndex, bool traceOn )
{
  if ( traceOn )
    lout[ cellIndex ] << "  Neuron[" << neuronIndex << "] ";

  assert( ! ( numOfInputs_ -1 - inputVectorWoBias.size() ) );  // -1 because the bias term is lack.

  double tmpOutput;
  tmpOutput = doLinearCombinationWtBias( cellIndex, inputVectorWoBias, weights_, traceOn );
  output_   = activationFunction( cellIndex, tmpOutput, traceOn );

  return    output_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

// The linear combination
//          M
// u_{k} = sum { w_{m}*x_{m} }
//         m=0

double
Neuron::doLinearCombinationWtBias( int cellIndex, const vdouble* tmpInputVectorWoBias, double* weights, bool traceOn )
{
  assert( ! ( numOfInputs_ -1 - tmpInputVectorWoBias->size() ) ); // -1 because the bias term is lack.

  int m;
  double linearCombination ( 0 );

  for ( m = 0; m < numOfInputs_ - 1 ; m++ )
  {
    linearCombination += weights_[ m ] * tmpInputVectorWoBias->at( m ) ;
    if ( traceOn )
    {
      if ( m == 0 )
        lout[ cellIndex ] << weights_[m] << "*" << tmpInputVectorWoBias->at(m);
      else
        lout[ cellIndex ] << " + " << weights_[m] << "*" << tmpInputVectorWoBias->at(m);
    }
  }
  linearCombination += weights_[ m ] * 1.0;  // for bias
  if ( traceOn )
    lout[ cellIndex ] << " + " << weights_[ m ] << "*1.0 = " << linearCombination << " "; // << endl;

  return linearCombination;
}

double
Neuron::doLinearCombinationWtBias( int cellIndex, const vdouble tmpInputVectorWoBias, double* weights, bool traceOn )
{
  assert( ! ( numOfInputs_ -1 - tmpInputVectorWoBias.size() ) ); // -1 because the bias term is lack.

  int m;
  double linearCombination ( 0 );

  for ( m = 0; m < numOfInputs_ - 1 ; m++ )
  {
    linearCombination += weights_[ m ] * tmpInputVectorWoBias.at( m ) ;
    if ( traceOn )
    {
      if ( m == 0 )
    	  lout[ cellIndex ] << weights_[m] << "*" << tmpInputVectorWoBias.at(m);
      else
        lout[ cellIndex ] << " + " << weights_[m] << " * " << tmpInputVectorWoBias.at(m);
    }
  }
  linearCombination += weights_[ m ] * 1.0;  // for bias
  if ( traceOn )
    lout[ cellIndex ] << " + " << weights_[ m ] << "*1.0 = " << linearCombination << " "; // << endl;

  return linearCombination;
}


double
Neuron::activationFunction( int cellIndex, double input, bool traceOn )
{
  // Input value to the activation function is
  // linear combination of input and weight vectors.

  // For my purpose, TANSIG apears the most frequenly, LINEAR is the second highest frequency.
  // LOGSIG is there for the safe of formality.

  assert( !activationFn_.empty() );

  double output;

  if ( activationFn_ == "tansig" )
  {
    output = tansigFunction( input );
    if ( traceOn )
      lout[ cellIndex ] << "tansig(" << input << ")=" << output << endl;
  }
  else if ( activationFn_ == "linear" )
  {
    output = input;
    if ( traceOn )
      lout[ cellIndex ] << "linear(" << input << ")=" << output << endl;
  }
  else if ( activationFn_ == "logsig" )
  {
    output = logsigFunction( input );
    if ( traceOn )
      lout[ cellIndex ] << "logsig(" << input << ")=" << output << endl;
  }
  else if ( activationFn_ == "floor" )
  {
    output = floor( input );
    if ( traceOn )
      lout[ cellIndex ] << "floor(" << input << ")=" << output << endl;
  }
  else if ( activationFn_ == "ternary_step" )
  {
    output = ternaryStepFunction( input, c_, w_ );
    if ( traceOn )
      lout[ cellIndex ] << "ternary_step(" << input << ")=" << output << endl;
  }
  else if ( activationFn_ == "mod_3" )
  {
    output = moduloThreeFunction( input );
    if ( traceOn )
      lout[ cellIndex ] << "mod_3(" << input << ")=" << output << endl;
  }
  else
  {
    cerr <<"Error: Wrong choice of activation function."<<endl;
    exit(1);
  }

  return output;
}

// REFERENCE
//   Simon Haykin, "Neural Networks: A comprehensive Foundation",
//                  Second edition, Person Education, 1999.
//   You may refer to:
//                  equation (1.12), 1.3. Models of a Neuron, page 14.
// REFERENCE

double
Neuron::logsigFunction( double input )
{
  // Log-sigmoid transfer function
  // output ranges from 0.0 to 1.0.
  double output;

  output = 1.0 / ( 1.0 + exp( -slopeParameterLogsig_ * input ) );

  return output;
}

// REFERENCE
//   http://www.mathworks.com/access/helpdesk/help/toolbox/nnet/tansig.html
//   This is mathematically equivalent to tanh(N).
// REFERENCE

double
Neuron::tansigFunction( double input )
{
  // Hyperbolic tangent sigmoid transfer function
  // output ranges from -1.0 to 1.0.
  double output;

  output = 2.0 / ( 1.0 + exp( -slopeParameterTansig_ * input ) ) - 1.0;

  return output;
}

double
Neuron::ternaryStepFunction( double input, double c, double w )
{
  double output;

  if ( input < (c-w/2) )
    output = 0.0;
  else if ( input < (c+w/2) )
    output = 1.0;
  else
    output = 2.0;

  return output;
}

// The variable output should be either 0,1 or 2.
// As a ternary value is used, modulo 3 is used.
//
//   "remainder = input % 3"
//
// is the desired operation, but an error occurs because the variable input is a floating point value, not an integer.
// The error message is
//   "invalid operands of types ‘double’ and ‘int’ to binary ‘operator%’".
//
// So perform the modulo-3 operation manually.
// For details, refer to http://en.wikipedia.org/wiki/Modulo_operation .
// In a nutshell, remainder is an integer in [0,1,2] when input is a floating value.
//   For example, when input=158.25,
// static_cast<int>( input/3 ) = static_cast<int>(52.75) = 52.
// remainder = 158.25 - 3 *52 = 158.25 -156 = 2.25 ==> 2 because remainder is an integer type variable.
//
// TODO: If the situation allows, double-check that the output value ranges from 0 to 2 and doesn't return a negative value.
// remainder = input - 3 * static_cast<int>( input/3 );  // It has a problem that the remainder can be negative.

double
Neuron::moduloThreeFunction( double input )
{
  double output;
  double q; // quotient
  double r; // remainder

  q = floor( input/3.0 );
  r = floor( input - 3.0*q );
  output = r;

  if ( mode_.empty() )  // This is the normal mode.
  {
    if ( output >2.0 || output < 0.0 )
	  cerr << "Error: double Neuron::moduloThreeFunction( double input ), output " << output << " is out of the range." << endl;
    return output;
  }
  else if ( mode_ == "test" )  // This is only when the activation function's input-output relationship is tested.
    return output;
}
