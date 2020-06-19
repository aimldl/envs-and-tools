#include  "ConfigDirStruct.hpp"
#include  "ConfigUtilFns.hpp"

//==============================================================================
//                            Public functions
//==============================================================================

ConfigDirStruct::ConfigDirStruct()
  :
  isGotoBookmark_( false ),
  dirGnuplotConfigFile_( "gnuplot_config_file" ),      dirGnuplotConfigFile_found_( false ),
  fileNnWeights_( "nn_weights.cnn" ),                  fileNnWeights_found_( false ),
  fileNnInitialWeights_( "nn_init_weights.cnn" ),      fileNnInitialWeights_found_( false ),
  fileGnuplotInput_( "weights.cnn" ),                  fileGnuplotInput_found_( false ),
  fileGnuplotOutput_( "gnuplot_output.ps" ),           fileGnuplotOutput_found_( false ),
  file_gnuplotInput_( "gnuplot_default.dat" ),         file_gnuplotInput_found_( false ),
  file_gnuplotConfig_( "gnuplot_default.gp" ),         file_gnuplotConfig_found_( false ),
  file_gnuplotOutput_( "gnuplot_default.ps" ),         file_gnuplotOutput_found_( false )
{
}

ConfigDirStruct::~ConfigDirStruct()
{
}

bool
ConfigDirStruct::process
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
    if ( !strcmpNoCase( name, "dir_gnuplot_config_file" ) )
    {
      validNameFlag = 1;
      if ( dirGnuplotConfigFile_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> dirGnuplotConfigFile_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << dirGnuplotConfigFile_ << "'" << endl;
        validValueFlag = 1;
        dirGnuplotConfigFile_found_ = true;
      }
      isGotoBookmark_ = true;      
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "file_nn_weights") )
    {
      validNameFlag = 1;
      if ( fileNnWeights_found_ == true )
      {
        alreadyFoundFlag = 1;
        goto bookmark;
      }
      if ( inputObj >> fileNnWeights_ || inputObj.eof() )
      {
        // Assertion error if output file is NOT specified.
        // Check your configuration file.
        // An example of an assertion error "fileNnWeights = "
        // Try "fileNnWeights = default.out" to fix this problem
        assert( inputObj );

        tout << "  Set '" << name << "' to '" << fileNnWeights_ << endl;
        validValueFlag = 1;
        fileNnWeights_found_ = true;
      }
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "file_nn_init_weights") )
    {
      validNameFlag = 1;
      if ( fileNnInitialWeights_found_ == true )
      {
        alreadyFoundFlag = 1;
        goto bookmark;
      }
      if ( inputObj >> fileNnInitialWeights_ || inputObj.eof() )
      {
        // Assertion error if output file is NOT specified.
        // Check your configuration file.
        // An example of an assertion error "fileNnInitialWeights = "
        // Try "fileNnInitialWeights = default.out" to fix this problem
        assert( inputObj );

        tout << "  Set '" << name << "' to '" << fileNnInitialWeights_ << endl;
        validValueFlag = 1;
        fileNnInitialWeights_found_ = true;
      }
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "file_gnuplot_input" ) )
    {
      validNameFlag = 1;
      if ( file_gnuplotInput_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> file_gnuplotInput_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << file_gnuplotInput_ << "'" << endl;
        validValueFlag = 1;
        file_gnuplotInput_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "file_gnuplot_config" ) )
    {
      validNameFlag = 1;
      if ( file_gnuplotConfig_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> file_gnuplotConfig_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << file_gnuplotConfig_ << "'" << endl;
        validValueFlag = 1;
        file_gnuplotConfig_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
    if ( !strcmpNoCase( name, "file_gnuplot_output" ) )
    {
      validNameFlag = 1;
      if ( file_gnuplotOutput_found_ == true )
      {
        alreadyFoundFlag = 1;
        isGotoBookmark_ = true;
        goto bookmark;
      }
      if ( inputObj >> file_gnuplotOutput_ || inputObj.eof() )
      {
        tout << "  Set '" << name << "' to '" << file_gnuplotOutput_ << "'" << endl;
        validValueFlag = 1;
        file_gnuplotOutput_found_ = true;
      }
      isGotoBookmark_ = true;
      goto bookmark;
    }

    //==========================================================================
 
  bookmark:

  return isGotoBookmark_;
}

string
ConfigDirStruct::get_dirGnuplotConfigFile_() const
{
  return dirGnuplotConfigFile_;
}

string
ConfigDirStruct::get_fileNnWeights_() const
{
  return fileNnWeights_;
}

string
ConfigDirStruct::get_fileNnInitialWeights_() const
{
  return fileNnInitialWeights_;
}

bool
ConfigDirStruct::get_fileNnWeights_found_() const
{
  return fileNnWeights_found_;
}

bool
ConfigDirStruct::get_fileNnInitialWeights_found_() const
{
  return fileNnInitialWeights_found_;
}

bool
ConfigDirStruct::get_dirGnuplotConfigFile_found_() const
{
  return dirGnuplotConfigFile_found_;
}

string
ConfigDirStruct::get_file_gnuplotInput_() const
{
  return file_gnuplotInput_;
}

string
ConfigDirStruct::get_file_gnuplotConfig_() const
{
  return file_gnuplotConfig_;
}

string
ConfigDirStruct::get_file_gnuplotOutput_() const
{
  return file_gnuplotOutput_;
}

bool
ConfigDirStruct::get_file_gnuplotConfig_found_() const
{
  return file_gnuplotConfig_found_;
}

bool
ConfigDirStruct::get_file_gnuplotInput_found_() const
{
  return file_gnuplotInput_found_;
}

bool
ConfigDirStruct::get_file_gnuplotOutput_found_() const
{
  return file_gnuplotOutput_found_;
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================
