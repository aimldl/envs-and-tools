#include  "ConfigNeuralNetworks.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigNeuralNetworks::ConfigNeuralNetworks()
  :
  isGotoBookmark_( false ),
  activationFunction_( 1 ),                 activationFunction_found_( false ),
  activationFunctionHiddenLayer_("tansig"), activationFunctionHiddenLayer_found_( false ),
  activationFunctionOutputLayer_("mod_3"),  activationFunctionOutputLayer_found_( false ),
  slopeParamLogsig_( 1 ),                   slopeParamLogsig_found_( false ),
  slopeParamTansig_( 1 ),                   slopeParamTansig_found_( false ),
  ternaryStepFn_c_( 0.0 ),                  ternaryStepFn_c_found_( false ),
  ternaryStepFn_w_( -1.0 ),                 ternaryStepFn_w_found_( false ),
  numOfNeuronsInLayers_( "none" ),          numOfNeuronsInLayers_found_( false )
{

}

ConfigNeuralNetworks::~ConfigNeuralNetworks()
{
}

bool
ConfigNeuralNetworks::process
(
  const char* name,
  ifstream&   inputObj,
  int&        validNameFlag,
  int&        validValueFlag,
  int&        alreadyFoundFlag 
)
{
  isGotoBookmark_ = false;

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_activation_function") )
    {
      validNameFlag = 1;
      if ( activationFunction_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> activationFunction_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << activationFunction_ << "'" << endl;
        if ( !( activationFunction_>=1 && activationFunction_<=9 ) )
        {
          cerr << "Error in class ConfigNeuralNetworks. Unknown value: \n"
               << "activationFunction_ = " << activationFunction_
               << endl;
          exit( 1 );
        }
        validValueFlag = 1;
        activationFunction_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_activation_function_hidden_layer") )
    {
      validNameFlag = 1;
      if ( activationFunctionHiddenLayer_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> activationFunctionHiddenLayer_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << activationFunctionHiddenLayer_ << "'" << endl;
        validate_typeOfActivationFunction( "neuralnets_activation_function_hidden_layer", activationFunctionHiddenLayer_ );
        validValueFlag = 1;
        activationFunctionHiddenLayer_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_activation_function_output_layer") )
    {
      validNameFlag = 1;
      if ( activationFunctionOutputLayer_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> activationFunctionOutputLayer_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << activationFunctionOutputLayer_ << "'" << endl;
        validate_typeOfActivationFunction( "neuralnets_activation_function_output_layer", activationFunctionOutputLayer_ );
        validValueFlag = 1;
        activationFunctionOutputLayer_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_slope_param_logsig") )
    {
      validNameFlag = 1;
      if ( slopeParamLogsig_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> slopeParamLogsig_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << slopeParamLogsig_ << "'" << endl;
        validValueFlag = 1;
        slopeParamLogsig_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_slope_param_tansig") )
    {
      validNameFlag = 1;
      if ( slopeParamTansig_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> slopeParamTansig_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << slopeParamTansig_ << "'" << endl;
        validValueFlag = 1;
        slopeParamTansig_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_number_of_neurons_in_layers") )
    {
      validNameFlag = 1;
      if ( numOfNeuronsInLayers_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> numOfNeuronsInLayers_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << numOfNeuronsInLayers_ << "'" << endl;
        numOfNeuronsInLayersVector_ = process_numOfNeuronsInLayers_( numOfNeuronsInLayers_ );
        totalNumOfLayers_ = numOfNeuronsInLayersVector_.size()+1;
        // When "neuralnets_number_of_neurons_in_layers" is used, the input layer is not specified.
        // In order to accurately compute totalNumOfLayers_, "1" should be added.

        vint::iterator itr;
        tout << "  Set '" << name << "' to '" << "\t" << "numOfNeuronsInLayersVector_ = ";
        for ( itr = numOfNeuronsInLayersVector_.begin(); itr < numOfNeuronsInLayersVector_.end(); itr++  )
          tout << "  Set '" << name << "' to '" << *itr << " ";
        tout << "  Set '" << name << "' to '" << endl;
        tout << "  Set '" << name << "' to '" << "\t" << "totalNumOfLayers_ = " << totalNumOfLayers_ << endl;

        validValueFlag = 1;
        numOfNeuronsInLayers_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_ternary_step_function_c") )
    {
      validNameFlag = 1;
      if ( ternaryStepFn_c_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> ternaryStepFn_c_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << ternaryStepFn_c_ << "'" << endl;
        validValueFlag = 1;
        ternaryStepFn_c_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
    if ( !strcmpNoCase( name, "neuralnets_ternary_step_function_w") )
    {
      validNameFlag = 1;
      if ( ternaryStepFn_w_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> ternaryStepFn_w_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << ternaryStepFn_w_ << "'" << endl;
        validValueFlag = 1;
        ternaryStepFn_w_found_ = true;
      }

      isGotoBookmark_ = true;
      goto bookmark;
    }
    //==========================================================================
 
  bookmark:

  return isGotoBookmark_;
}

int
ConfigNeuralNetworks::get_activationFunction_() const
{
  return activationFunction_;
}

double
ConfigNeuralNetworks::get_slopeParamLogsig_() const
{
  return slopeParamLogsig_;
}

double
ConfigNeuralNetworks::get_slopeParamTansig_() const
{
  return slopeParamTansig_;
}

double
ConfigNeuralNetworks::get_ternaryStepFn_c_() const
{
  return ternaryStepFn_c_;
}

double
ConfigNeuralNetworks::get_ternaryStepFn_w_() const
{
  return ternaryStepFn_w_;
}

string
ConfigNeuralNetworks::get_numOfNeuronsInLayers_() const
{
  return numOfNeuronsInLayers_;
}

int
ConfigNeuralNetworks::get_totalNumOfLayers_() const
{
  return totalNumOfLayers_;
}

vint
ConfigNeuralNetworks::get_numOfNeuronsInLayersVector_() const
{
  return numOfNeuronsInLayersVector_;
}

string
ConfigNeuralNetworks::get_activationFunctionHiddenLayer_() const
{
  return activationFunctionHiddenLayer_;
}

string
ConfigNeuralNetworks::get_activationFunctionOutputLayer_() const
{
  return activationFunctionOutputLayer_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

// An example of the number of neurons specified in a config file is below.
//
//   "neuralnets_number_of_neurons_in_layers = 3:2:1"
//
// A string "3:2:1" is stored in numOfNeuronsInLayers.
//
// The following function "process_numOfNeuronsInLayers_" processes the string in order
// to find the number of hidden layers.

vint
ConfigNeuralNetworks::process_numOfNeuronsInLayers_( string numOfNeuronsInLayers )
{
  vint  numOfNeuronsInLayersVector;  // For readability

  numOfNeuronsInLayersVector
    = MyStringUtilFunctions::str2ints( numOfNeuronsInLayers );

  return numOfNeuronsInLayersVector;
}

// stringInConfigFile is either neuralnets_activation_function_hidden_layer
//                           or neuralnets_activation_function_output_layer.
void
ConfigNeuralNetworks::validate_typeOfActivationFunction( string stringInConfigFile, string activationFunction )
{
  if (
	   activationFunction != "tansig"
         &&
       activationFunction != "mod_3"
         &&
       activationFunction != "logsig"
         &&
       activationFunction != "linear"
         &&
       activationFunction != "floor"
         &&
       activationFunction != "ternary_step"
     )
  {
    cerr << "Error in class ConfigNeuralNetworks. Unknown value: \n"
         << stringInConfigFile << " = " << activationFunction << "."
         << endl;
    exit( 1 );
  }
}
