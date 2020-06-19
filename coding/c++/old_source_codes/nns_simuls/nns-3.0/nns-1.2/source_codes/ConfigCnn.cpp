#include  "ConfigCnn.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigCnn::ConfigCnn()
  :
  isGotoBookmark_( false ),
  maxEpoch_o_( 1 ),                             maxEpoch_o_found_( false ),
  maxEpochs_i_( 1 ),                            maxEpochs_i_found_( false ),
  targetSystemError_( -1.0 ),                   targetSystemError_found_( false ),
  targetCellError_( -1.0 ),                     targetCellError_found_( false ),
  fdInputInitialization_( "random" ),           fdInputInitialization_found_( false ),
  errorMetric_( "mse"),                         errorMetric_found_( false ),
  trainingAlgorithm_( "none" ),                 trainingAlgorithm_found_( false ),
  nnType_( "none" ),                            nnType_found_( false ),
  matchNnInitialWeightsToTrainingAlgo_( true ), matchNnInitialWeightsToTrainingAlgo_found_( false ),
  initialWeightsMode_("random"),                initialWeightsMode_found_( false )
{

}

ConfigCnn::~ConfigCnn()
{
}

bool
ConfigCnn::process
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
    if ( !strcmpNoCase( name, "cnn_max_epoch_o" ) )
    {
      validNameFlag = 1;
      if ( maxEpoch_o_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> maxEpoch_o_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << maxEpoch_o_ << "'" << endl;
        validValueFlag = 1;
        maxEpoch_o_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_max_epoch_i") )
    {
      validNameFlag = 1;
      if ( maxEpochs_i_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> maxEpochs_i_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << maxEpochs_i_ << "'" << endl;
        validValueFlag = 1;
        maxEpochs_i_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_target_system_error" ) )
    {
      validNameFlag = 1;
      if ( targetSystemError_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> targetSystemError_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << targetSystemError_ << "'" << endl;
        validValueFlag = 1;
        targetSystemError_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_target_cell_error" ) )
    {
      validNameFlag = 1;
      if ( targetCellError_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> targetCellError_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << targetCellError_ << "'" << endl;
        validValueFlag = 1;
        targetCellError_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_fd_input_initialization" ) )
    {
      validNameFlag = 1;
      if ( fdInputInitialization_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> fdInputInitialization_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << fdInputInitialization_ << "'" << endl;
        validate_fdInputInitialization_();
        validValueFlag = 1;
        fdInputInitialization_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }
    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_error_metric" ) )
    {
      validNameFlag = 1;
      if ( errorMetric_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> errorMetric_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << errorMetric_ << "'" << endl;
        validate_errorMetric_();
        validValueFlag = 1;
        errorMetric_found_ = true;
      }

      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_training_algorithm" ) )
    {
      validNameFlag = 1;
      if ( trainingAlgorithm_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> trainingAlgorithm_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << trainingAlgorithm_ << "'" << endl;
        validate_trainingAlgorithm_();
        validValueFlag = 1;
        trainingAlgorithm_found_ = true;
      }

      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_nn_type" ) )
    {
      validNameFlag = 1;
      if ( nnType_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> nnType_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << nnType_ << "'" << endl;
        validate_nnType_();
        validValueFlag = 1;
        nnType_found_ = true;
      }

      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_initial_weights_mode") )
    {
      validNameFlag = 1;
      if ( initialWeightsMode_found_ == true )      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> initialWeightsMode_ || inputObj.eof() )
      {
      	assert( inputObj );
      	tout << "  Set '" << name << "' to '" << initialWeightsMode_ << "'" << endl;
      	validate_initialWeightsMode_();
        validValueFlag = 1;
        initialWeightsMode_found_ = true;
      }
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "cnn_match_init_weights_to_training_algo" ) )
    {
      validNameFlag = 1;
      if ( matchNnInitialWeightsToTrainingAlgo_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> matchNnInitialWeightsToTrainingAlgo_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << matchNnInitialWeightsToTrainingAlgo_ << "'" << endl;
        validate_matchNnInitialWeightsToTrainingAlgo_();
        validValueFlag = 1;
        matchNnInitialWeightsToTrainingAlgo_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
 
  bookmark:

  return isGotoBookmark_;
}

int
ConfigCnn::get_maxEpoch_o_() const
{
  return maxEpoch_o_;
}

int
ConfigCnn::get_maxEpochs_i_() const
{
  return maxEpochs_i_;
}

double
ConfigCnn::get_targetSystemError_() const
{
  return targetSystemError_;
}

double
ConfigCnn::get_targetCellError_() const
{
  return targetCellError_;
}

string
ConfigCnn::get_trainingAlgorithm_() const
{
  return trainingAlgorithm_;
}

string
ConfigCnn::get_nnType_() const
{
  return nnType_;
}

bool
ConfigCnn::get_matchNnInitialWeightsToTrainingAlgo_() const
{
  return matchNnInitialWeightsToTrainingAlgo_;
}

string
ConfigCnn::get_fdInputInitialization_() const
{
  return fdInputInitialization_;
}

string
ConfigCnn::get_errorMetric_() const
{
  return errorMetric_;
}

string
ConfigCnn::get_initialWeightsMode_() const
{
  return initialWeightsMode_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
ConfigCnn::validate_fdInputInitialization_()
{
  if (
       fdInputInitialization_ != "zeros"
         &&
       fdInputInitialization_ != "ones"
         &&
       fdInputInitialization_ != "random"
         &&
       fdInputInitialization_ != "rand_ternary"
         &&
       fdInputInitialization_ != "target"
     )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "cnn_fd_input_initialization = " << fdInputInitialization_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigCnn::validate_errorMetric_()
{
  if (
       errorMetric_ != "mse"
         &&
       errorMetric_ != "abs_error"
     )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "cnn_error_metric = " << errorMetric_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigCnn::validate_trainingAlgorithm_()
{
  if (
       trainingAlgorithm_ != "pso"

     )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "cnn_training_algorithm = " << trainingAlgorithm_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigCnn::validate_nnType_()
{
  if ( nnType_ != "mlp" && nnType_ != "psrn" && nnType_ != "csrn" && nnType_ != "mcsrn" )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "cnn_nn_type = " << nnType_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigCnn::validate_matchNnInitialWeightsToTrainingAlgo_()
{
  if (
       matchNnInitialWeightsToTrainingAlgo_ != true   // 1
         &&
       matchNnInitialWeightsToTrainingAlgo_ != false  // 0
     )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "cnn_match_init_weights_to_training_algo = " << matchNnInitialWeightsToTrainingAlgo_ << "."
         << endl;
    exit( 1 );
  }
}

void
ConfigCnn::validate_initialWeightsMode_()
{
  if ( !( initialWeightsMode_== "random" || initialWeightsMode_ == "load_manually" ) )
  {
    cerr << "Error in class ConfigCnn. Unknown value: \n"
         << "initialWeightsMode_ = " << initialWeightsMode_
         << endl;
    exit( 1 );
  }
}
