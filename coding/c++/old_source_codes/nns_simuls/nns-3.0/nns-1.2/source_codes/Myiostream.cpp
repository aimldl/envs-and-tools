#include "Myiostream.hpp"
#include  "Config.hpp"
#include <sstream>  // For stringstream

ofstream  Myiostream::nout_init;
ifstream  Myiostream::nin_init;
ofstream  Myiostream::nout;
ofstream  Myiostream::eout;
ofstream  Myiostream::tout;
ofstream  Myiostream::pout;
ofstream  Myiostream::dout;
ofstream* Myiostream::lout;

bool      Myiostream::trace4dbg_;
bool      Myiostream::isDefaultValuesSet_;
bool      Myiostream::is_dir_outputFiles_set_;
bool      Myiostream::is_dir_configFiles_set_;
string    Myiostream::initialWeightsMode_;

string    Myiostream::dir_outputFiles_;
string    Myiostream::dir_configFiles_;
string    Myiostream::dir_root_;
string    Myiostream::dir_bin_;
string    Myiostream::file_config_;
string    Myiostream::file_trace_;
string    Myiostream::file_debug_;
string    Myiostream::file_nnWeights_;
string    Myiostream::file_nnInitialWeights_;
string    Myiostream::file_ErrorProfile_;
string    Myiostream::dir_gnuplotConfigFile_;
string    Myiostream::file_gnuplotConfig_;
string    Myiostream::file_gnuplotInput_;
string    Myiostream::gnuplotInputFileWithFullPath_;
string    Myiostream::file_gnuplotOutput_;
string    Myiostream::gnuplotOutputFileWithFullPath_;

string    Myiostream::file_config_with_path_;
string    Myiostream::file_trace_with_path_;
string    Myiostream::file_debug_with_path_;
string    Myiostream::file_nnWeights_with_path_;
string    Myiostream::file_nnInitialWeights_with_path_;
string    Myiostream::file_ErrorProfile_with_path_;
string    Myiostream::file_gnuplotConfig_with_path_;

bool      Myiostream::is_lout_set_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// The default values will be used in class ShellCommands and CommandLineArguments.

void
Myiostream::setDefaultValues()
{
  dir_bin_                = "bin";
  dir_configFiles_        = "config_files";
  dir_gnuplotConfigFile_  = "gnuplot_config_files";
  dir_outputFiles_        = "outputs";

  file_config_            = "default.cfg";
  file_trace_             = "default.trc";
  file_debug_             = "debug_info.trc";
  file_ErrorProfile_      = "error.prf";

  is_dir_outputFiles_set_ = false;
  is_dir_configFiles_set_ = false;
  trace4dbg_              = false;

  isDefaultValuesSet_ = true;
}

// numOfCells is computed twice in this class and class Cnn. It's logically
// appropriate to compute numOfCells in class Cnn, but class Cnn inherits this
// class, so it's inevitable to compute numOfCells twice.

void
Myiostream::configure( Config& configObj )
{
  assert( !dir_outputFiles_.empty() );

  set_tout( file_trace_with_path_ );
  set_eout( file_ErrorProfile_with_path_ );

  if  ( ( configObj.get_simulationsObj_().get_taskType_() == "cmlp_string_count" )
	 || ( configObj.get_simulationsObj_().get_taskType_() == "learn_optimal_moves" ) )
  {
    int numOfCells = configObj.get_simulationsObj_().get_boardSize_()*configObj.get_simulationsObj_().get_boardSize_();
    assert( ( numOfCells > 0 ) );
    lout = new ofstream [ numOfCells ];
    is_lout_set_ = true;

    set_nout( file_nnWeights_with_path_ );

    assert( !initialWeightsMode_.empty() );
    set_nout_init_or_nin_init( file_nnInitialWeights_with_path_, initialWeightsMode_ );

    set_lout( dir_outputFiles_, numOfCells );
    set_pout( file_gnuplotConfig_with_path_ );  // TODO: Check if this needs an if statement.
  }

  if ( configObj.get_simulationsObj_().get_trace4dbg_() )
    set_dout( file_debug_with_path_ );
}

void
Myiostream::closeAllIosInstances( const int numOfCells )
{
  nout.close();
  if ( initialWeightsMode_ == "random" )
    nout_init.close();
  else if ( initialWeightsMode_ == "load_manually" )
    nin_init.close();
  eout.close();
  tout.close();
  pout.close();
  for ( int c = 0; c < numOfCells; c++ )
    lout[c].close();

  if ( trace4dbg_ )
    dout.close();
}

//==============================================================================
//                        Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================
Myiostream::Myiostream()
{
}

Myiostream::~Myiostream()
{
}

string
Myiostream::get_dir_outputFiles_() const
{
  return dir_outputFiles_;
}

string
Myiostream::get_dir_configFiles_() const
{
  return dir_configFiles_;
}

string
Myiostream::get_dir_bin_() const
{
  return dir_bin_;
}

string
Myiostream::get_file_config_() const
{
  return file_config_;
}

string
Myiostream::get_file_trace_() const
{
  return file_trace_;
}

string
Myiostream::get_file_debug_() const
{
  return file_debug_;
}

bool
Myiostream::get_isDefaultValuesSet_() const
{
  return isDefaultValuesSet_;
}

// It is assumed all the executables nns-1.2.exe are located one level below the project
// root directory.

string
Myiostream::extract_dir_root_( const string cwd )
{
  assert( !cwd.empty() );

  string dir_root;
  size_t found;

  found = cwd.find_last_of("/\\");  // This should work both for linux and windows.
  dir_root = cwd.substr(0, found);

  cout << "Extracted dir_root: " << dir_root << " from cwd: " << cwd << endl;

  return dir_root;
}

//==============================================================================
//                            Protected functions
//==============================================================================

// If this function is used to specify filenameWithFullPath, dir_target is assumed
// to have the full path information.

string
Myiostream::appendStrings( const string dir_target, const string filename )
{
  assert( !dir_target.empty() );
  assert( !filename.empty() );

  string fullPath;
  string filenameWithFullPath;

  fullPath = dir_target;
  filenameWithFullPath = fullPath + "/" + filename;

//  cout << "    fullPath             = " << fullPath << endl;
//  cout << "    filename             = " << filename << endl;
//  cout << "    filenameWithFullPath = " << filenameWithFullPath << endl;

  return filenameWithFullPath;
}

// If this function is used to specify filenameWithFullPath, it is assumed dir_target
// does not have the full path information.

string
Myiostream::appendStrings( const string dir_root, const string dir_target, const string filename )
{
  assert( !dir_root.empty() );
  assert( !dir_target.empty() );
  assert( !filename.empty() );

  string fullPath;
  string filenameWithFullPath;

  fullPath = dir_root + "/" + dir_target;
  filenameWithFullPath = fullPath + "/" + filename;

//  cout << "    fullPath             = " << fullPath << endl;
//  cout << "    filename             = " << filename << endl;
//  cout << "    filenameWithFullPath = " << filenameWithFullPath << endl;

  return filenameWithFullPath;
}

// This function is supposed to be called in class Config after the file names are updated.
// So do not erase this function.
void
Myiostream::updateFileNamesWithPath()
{
  assert( !dir_root_.empty() );
  assert( !dir_outputFiles_.empty() );
  assert( !file_trace_.empty() );
  assert( !file_ErrorProfile_.empty() );

  if ( is_dir_outputFiles_set_ )
  {
    file_trace_with_path_           = appendStrings( dir_outputFiles_, file_trace_ );
    file_ErrorProfile_with_path_    = appendStrings( dir_outputFiles_, file_ErrorProfile_ );
    file_debug_with_path_           = appendStrings( dir_outputFiles_, file_debug_ );
  }
  else
  {
    file_trace_with_path_           = appendStrings( dir_root_, dir_outputFiles_, file_trace_ );
    file_ErrorProfile_with_path_    = appendStrings( dir_root_, dir_outputFiles_, file_ErrorProfile_ );
    file_debug_with_path_           = appendStrings( dir_root_, dir_outputFiles_, file_debug_ );
  }
}

// This function is supposed to be called in class Config after the file names are updated.
// So do not erase this function.
void
Myiostream::updateFileNamesWithPathForCnn()
{
  assert( !dir_root_.empty() );
  assert( !initialWeightsMode_.empty() );

  if ( is_dir_outputFiles_set_ )
  {
    file_nnWeights_with_path_       = appendStrings( dir_outputFiles_, file_nnWeights_ );
  }
  else
  {
    file_nnWeights_with_path_       = appendStrings( dir_root_, dir_outputFiles_, file_nnWeights_ );
  }

  // If random initial weights are chosen, those initial weights will be saved in a trace file in directory outputs.
  // When the initial weights are manually loaded from a file, the file should be located in directory config_files.
  if ( initialWeightsMode_ == "random" )
  {
    if ( is_dir_outputFiles_set_ )
      file_nnInitialWeights_with_path_  = appendStrings( dir_outputFiles_, file_nnInitialWeights_ );
    else
      file_nnInitialWeights_with_path_  = appendStrings( dir_root_, dir_outputFiles_, file_nnInitialWeights_ );
  }
  else if ( initialWeightsMode_ == "load_manually" )
  {
    if ( is_dir_configFiles_set_ )
      file_nnInitialWeights_with_path_  = appendStrings( dir_configFiles_, file_nnInitialWeights_ );
    else
      file_nnInitialWeights_with_path_  = appendStrings( dir_root_, dir_configFiles_, file_nnInitialWeights_ );
  }

  file_gnuplotConfig_with_path_     = appendStrings( dir_root_, dir_gnuplotConfigFile_, file_gnuplotConfig_ );
  gnuplotInputFileWithFullPath_     = appendStrings( dir_root_, dir_gnuplotConfigFile_, file_gnuplotInput_ );
  gnuplotOutputFileWithFullPath_    = appendStrings( dir_root_, dir_gnuplotConfigFile_, file_gnuplotOutput_ );
}
//==============================================================================
//                            Private functions
//==============================================================================

void
Myiostream::set_nout_init_or_nin_init( string fileNnInitialWeightsWithFullPath, string initialWeightsMode )
{
  assert( !fileNnInitialWeightsWithFullPath.empty() );
  assert( !initialWeightsMode.empty() );

  if ( initialWeightsMode == "random" )
  {
    // When the neural networks' weights are initialized randomly, the initial weights are saved to a file.
    // So the initial weights are saved to a file. Consequently, an output file stream should be opened.
    cout << "Opening \"" << fileNnInitialWeightsWithFullPath << "\"" << endl;
    nout_init.open( fileNnInitialWeightsWithFullPath.c_str(), ios::out );
    if ( !nout_init )
    {
      cout << "Cannot open \"" << fileNnInitialWeightsWithFullPath << "\"" << endl;
      exit( 1 );
    }
  }
  else if ( initialWeightsMode == "load_manually" )
  {
    // When the neural networks' weights are loaded manually, the initial weights are read from a file.
    // So an input file stream should be opened.

    cout << "Opening \"" << fileNnInitialWeightsWithFullPath << "\"" << endl;
    nin_init.open( fileNnInitialWeightsWithFullPath.c_str(), ios::in );
    if ( !nin_init )
    {
      cerr << "Cannot open \"" << fileNnInitialWeightsWithFullPath << "\"" << endl;
      exit( 1 );
    }
  }  // Impossible options should be screened out at the time when the mode is read from a config file, so no else statement.
}

void
Myiostream::set_nout( string fileNnWeightsWithFullPath )
{
  assert( !fileNnWeightsWithFullPath.empty() );

  cout << "Opening \"" << fileNnWeightsWithFullPath << "\"" << endl;
  nout.open( fileNnWeightsWithFullPath.c_str(), ios::out );
  if ( !nout )
  {
    cout << "Cannot open \"" << fileNnWeightsWithFullPath << "\"" << endl;
    exit( 1 );
  }

  nout << "# " << fileNnWeightsWithFullPath << endl;
}

void
Myiostream::set_tout( string fileTraceWithFullPath )
{
  assert( !fileTraceWithFullPath.empty() );

  cout << "Opening \"" << fileTraceWithFullPath << "\"" << endl;
  tout.open( fileTraceWithFullPath.c_str(), ios::out );
  if ( !tout )
  {
    cout << "Cannot open \"" << fileTraceWithFullPath << "\"" << endl;
    exit( 1 );
  }

  tout << "# " << fileTraceWithFullPath << endl;
}

void
Myiostream::set_dout( string fileDebugWithFullPath )
{
  assert( !fileDebugWithFullPath.empty() );

  cout << "Opening \"" << fileDebugWithFullPath << "\"" << endl;
  dout.open( fileDebugWithFullPath.c_str(), ios::out );
  if ( !dout )
  {
    cout << "Cannot open \"" << fileDebugWithFullPath << "\"" << endl;
    exit( 1 );
  }

  dout << "# " << fileDebugWithFullPath << endl;
}

void
Myiostream::set_pout( string fileGnuplotConfigFileWithFullPath )
{
  assert( !fileGnuplotConfigFileWithFullPath.empty() );

  cout << "Opening \"" << fileGnuplotConfigFileWithFullPath << "\"" << endl;
  cout << "  Generating a gnuplot configuration file '" << fileGnuplotConfigFileWithFullPath << "'..." << endl;
  pout.open( fileGnuplotConfigFileWithFullPath.c_str(), ios::out );
  if ( !pout )
  {
    cout << "Cannot open \"" << fileGnuplotConfigFileWithFullPath << "\"" << endl;
    exit( 1 );
  }
  pout << "  set xlabel \"x\"\n"
       << "  set ylabel \"y\"\n"
       << "  set xrange [-1:1]\n"
       << "  set yrange [-1:1]\n"
       << "  set title \"" << "TEST" <<"\"\n"
       << "  set xzeroaxis\n"
       << "  set yzeroaxis\n"
       << "  set output \"" << file_gnuplotConfig_with_path_ << "\"\n"
       << "  set term postscript\n"
       << "  plot \"" << gnuplotInputFileWithFullPath_ << "\" using 1:2 with lines\n"
       << "  save \"" << gnuplotOutputFileWithFullPath_ << "\"\n";
  pout.close();
}

void
Myiostream::set_eout( string fileErrorProfileWithFullPath )
{
  cout << "Opening \"" << fileErrorProfileWithFullPath << "\"" << endl;
  eout.open( fileErrorProfileWithFullPath.c_str(), ios::out );
  if ( !eout )
  {
    cout << "Cannot open \"" << fileErrorProfileWithFullPath << "\"" << endl;
    exit( 1 );
  }
  eout << "# " << fileErrorProfileWithFullPath << endl;
}

// Each cell logs a different trace file, so open the same number of files as the number of cells.

void
Myiostream::set_lout( const string dir_outputFiles, const int numOfCells )
{
  assert( is_lout_set_ );
  assert( !dir_root_.empty() );

  stringstream ss;  // In order to convert an integer to ascii without using the non-standard function itoa
  string filename;  // e.g. cell_0.trc, cell_1.trc, etc.
  string filename_with_path_;

  for ( int c = 0; c < numOfCells; c++ )
  {
	ss << c;
	filename = "cell_" + ss.str() + ".trc";;

    if ( is_dir_outputFiles_set_ )
      filename_with_path_ = appendStrings( dir_outputFiles_, filename );
    else
      filename_with_path_ = appendStrings( dir_root_, dir_outputFiles_, filename );

    cout << "Opening \"" << filename_with_path_ << endl;
	lout[c].open( filename_with_path_.c_str(), ios::out );
	if ( !lout[c] )
	{
	  cout << "Cannot open \"" << filename_with_path_ << endl;
	  exit( 1 );
	}
	else
	{
      lout[ c ] << "# " << filename_with_path_ << "\n"
                << "# A log file for cell " << c << "\n"
                << "#   Only important cell activities are logged in this file.\n"
                << "#   These events includes:\n"
                << "#     initial neural network weights,\n"
                << "#     best PSO particles,\n"
                << "#     neural network behavior only for the best PSO particle.\n"
                << "#     cell and system errors, \n"
                << "#     the name of function associated with the log.\n"
                << "#   Logging all the cell activities is not preffered because of several reasons.\n"
                << "#     Reason 1: the log file becomes too large.\n"
                << "#     Reason 2: most of the information in the huge log file is redundant.\n"
                << "#     Reason 3: so the log file is almost impossible to understand.\n"
                << "#     Reason 4: the program runs much slower to log unneccessary data. \n"
                << "#   Out of the above reasons, logging essential events is better than logging all cell activities. \n"
                << "#\n"
                << "#   One may use other terminal commands such as cat and grep to simplify the analysis of the trace file. \n"
                << "#   For example,\n"
                << "#     $ cat cell_0.trc | grep \"Best particle\"\n"
                << "#     time_o=0 time_i=0 Best particle: 8 \n"
                << "#     time_o=0 time_i=1 Best particle: 8\n"
                << "#     time_o=19 time_i=99 Best particle: 2 6\n"
                << "#     time_o=23 time_i=116 Best particle: 2 6\n"
                << "#     time_o=45 time_i=229 Best particle: 7\n"
                << "#" << endl;
	}
	filename.clear();
	filename_with_path_.clear();
	ss.str("");  // Reset like this. close() flush() didn't work.
  }
}
