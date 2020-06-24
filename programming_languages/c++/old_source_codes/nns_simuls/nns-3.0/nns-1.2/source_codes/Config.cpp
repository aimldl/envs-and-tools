#include  "Config.hpp"
#include  "ConfigUtilFns.hpp"

bool
Config::isConfigured_;

//==============================================================================
//                        Static Public functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

Config::Config( const string& cwd )
{
  isConfigured_ = false;

  dir_root_ = extract_dir_root_( cwd );

  if ( is_dir_configFiles_set_ )
    file_config_with_path_ = appendStrings( dir_configFiles_, file_config_ );
  else
    file_config_with_path_ = appendStrings( dir_root_, dir_configFiles_, file_config_ );

  openConfigFile( file_config_with_path_ );
  processConfigClasses();

  updateFileNamesWithPath();  // From class Myiostream

  if  ( ( simulationsObj_.get_taskType_() == "cmlp_string_count" )
  	 || ( simulationsObj_.get_taskType_() == "learn_optimal_moves" ) )
  {
    initialWeightsMode_ = cnnObj_.get_initialWeightsMode_();

    if ( ! simulationsObj_.get_postprocess_() )
      cout << "simul_postprocess is turned off." << endl;

    if ( dirStructObj_.get_dirGnuplotConfigFile_found_() )
      dir_gnuplotConfigFile_ = dirStructObj_.get_dirGnuplotConfigFile_();

    if ( dirStructObj_.get_fileNnWeights_found_() )
      file_nnWeights_         = dirStructObj_.get_fileNnWeights_();
    else
      file_nnWeights_ = "nnets_weights.cnn";

    if ( dirStructObj_.get_fileNnInitialWeights_found_() )
      file_nnInitialWeights_ = dirStructObj_.get_fileNnInitialWeights_();
    else
      file_nnInitialWeights_ = "nn_init_weights.cnn";

    if ( dirStructObj_.get_file_gnuplotConfig_found_() )
      file_gnuplotConfig_    = dirStructObj_.get_file_gnuplotConfig_();

    if ( dirStructObj_.get_file_gnuplotInput_found_() )
      file_gnuplotInput_     = dirStructObj_.get_file_gnuplotInput_();

    if ( dirStructObj_.get_file_gnuplotOutput_found_() )
      file_gnuplotOutput_    = dirStructObj_.get_file_gnuplotOutput_();

    updateFileNamesWithPathForCnn();  // From class Myiostream
  }

  if ( simulationsObj_.get_trace4dbg_found_() )
    trace4dbg_ = simulationsObj_.get_trace4dbg_();

  isConfigured_ = true;
}

Config::~Config()
{
}

bool
Config::get_isConfigured_() const
{
  return isConfigured_;
}

ConfigSimulations
Config::get_simulationsObj_() const
{
  return simulationsObj_;
}

ConfigDirStruct
Config::get_dirStructObj_() const
{
  return dirStructObj_;
}

ConfigData
Config::get_dataObj_() const
{
  return dataObj_;
}

ConfigNeuralNetworks
Config::get_neuralNetsObj_() const
{
  return neuralNetsObj_;
}

ConfigPso
Config::get_psoObj_() const
{
  return psoObj_;
}

ConfigGnuPlot
Config::get_gnuPlotObj_() const
{
  return gnuPlotObj_;
}

ConfigCnn
Config::get_cnnObj_() const
{
  return cnnObj_;
}

ConfigReinLearning
Config::get_rlObj_() const
{
  return rlObj_;
}

void
Config::close_configFile()
{
  inputObj_.close();
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
void
Config::openConfigFile( const string fileConfigFileWithFullPath )
{
  assert( !fileConfigFileWithFullPath.empty() );

  cout << "Opening \"" << fileConfigFileWithFullPath << "\"" << endl;
  inputObj_.open( fileConfigFileWithFullPath.c_str() );
  if ( !inputObj_ )
  {
    cerr << "Error: Cannot open \"" << fileConfigFileWithFullPath << "\"\n" << endl;
    exit( 1 );
  }
}

void
Config::openConfigFile( const string dir_root, const string dir_configFiles, const string file_config )
{
  assert( !dir_root.empty() );
  assert( !dir_configFiles.empty() );
  assert( !file_config.empty() );

  file_config_with_path_ = appendStrings( dir_root, dir_configFiles, file_config );

  cout << "Opening \"" << file_config_with_path_ << "\"" << endl;
  inputObj_.open( file_config_with_path_.c_str() );
  if ( !inputObj_ )
  {
    cerr << "Error: Cannot open \"" << file_config_with_path_ << "\"\n" << endl;
    exit( 1 );
  }
}

// void Config::processConfigClasses()
//   is the core of class Config.
//   Change this function to add a new parameter to a config file.

void
Config::processConfigClasses()
{
  assert ( inputObj_ );

  char name[ 256 ] = {'\0'};
  string temp;
  for ( int validNameFlag = 0, validValueFlag = 0, alreadyFoundFlag = 0;
        inputObj_; validNameFlag = 0, validValueFlag = 0, alreadyFoundFlag = 0 )
  {
    // get variable name, skip whitespacesa and name-value separators '=' or ':'.
    getName( inputObj_, name );

    if ( name[0] == '\0' )
      continue;

//    tout << "      Set '" << name << "' to '";
    //==========================================================================
    // CLASS WITH NEW CONFIGURATION PARAMETERS
    // If a variable is found in process( ... ), it returns true.
    // So, go to bookmark.
    // Otherwise, move onto next.
    //==========================================================================

    if ( simulationsObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( dataObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( neuralNetsObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( psoObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( gnuPlotObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( cnnObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( dirStructObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    if ( rlObj_.process( name, inputObj_, validNameFlag, validValueFlag, alreadyFoundFlag ) )
      goto bookmark;

    bookmark:

    // Design issue:
    //   The following lines are unneccessary if only ConfigClasses are used.
    //   However, leave them here just in case some ConfigParams are processed
    //   in class Config.

    // Check abnomality of a line read at this iteration.
    if ( alreadyFoundFlag )
	{
	  cout << "Error: Variable '" << name << "' is already defined in the config file" << endl;
      exit(1);
	}
    if( !validNameFlag )
    {
	  cout << "Error: Unknown variable name '" << name << "' in the config file" << endl;
        exit(1);
    }
    else if( !validValueFlag )
    {
	  cout << "Error: Wrong value (for the given variable type) for '" << name << "' in the config file" << endl;
      exit(1);
    }
  }
}
