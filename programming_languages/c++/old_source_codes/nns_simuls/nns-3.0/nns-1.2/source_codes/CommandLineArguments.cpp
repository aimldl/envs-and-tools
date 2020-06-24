#include  "CommandLineArguments.hpp"

//==============================================================================
//                        Static Public functions
//==============================================================================
//==============================================================================
//                        Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

CommandLineArguments::CommandLineArguments( int argc, char* argv[] )
: releaseDate_( "Mar. 19, 2011" ), versionNumber_( "1.2" )
{
  assert( isDefaultValuesSet_ );

  process( argc, argv );
}

CommandLineArguments::~CommandLineArguments()
{
}
//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
CommandLineArguments::process( int argc, char* argv[] )
{
  programName_ = argv[0];  // Expecting nns.exe or nns_dbg.exe
  GetOpt getopt( argc, argv, "hv");
  processCommandLineOptions( getopt );
  processFileNames( getopt );
  cout << "  argv[0] = " << argv[0] << endl;
}

// Take care of the command ine options, e.g. -h, -v.
void
CommandLineArguments::processCommandLineOptions( GetOpt& getopt )
{
  // string programName_ should be set first. Some old compilers may fail here.
  assert( !programName_.empty() );
  int opt_char;

  while ( (opt_char=getopt()) != EOF )
  {
    switch (opt_char)
    {
      case 'h': ShowVersionInformation();
                ShowUsage();
                exit(1);
                break;
      case 'v': ShowVersionInformation();
                exit(1);
                break;
      default:
                ShowDefaultMessage();
                exit(1);
    }
  }
}

// void CommandLineArguments::processFileNames( GetOpt& getopt )
//   takes care of the configuration file name.
//   This function has a lot to do with class Config.
void
CommandLineArguments::processFileNames( GetOpt& getopt )
{
  // Index of the first argument except the options
  int    argIndex = getopt.optind;
  int    argc     = getopt.nargc;
  char** argv     = getopt.nargv;

  string tmpString;
  size_t found;

//  cout << "  (argc,argIndex)=("<<argc<<","<<argIndex<<")\n";
//  cout << "  argv[" << argIndex << "]=" << argv[ argIndex ] << endl;

  if ( argc - argIndex <= 0 )       // No input argument.
    cout << "  No input argement. The default config file will be used." << endl;
  else if ( argc - argIndex == 1 )  // One input argument.
  {                            // Assume the config file is given.
	// The first input argument contains a config file name and possibly its directory information.
	// If it has a file name followed by the directory information, split them and store separately.
    tmpString        = argv[ argIndex ];
    found            = tmpString.find_last_of("/\\");  // This should work both for linux and windows.

    if ( found == string::npos )  // If no separator, e.g. "/", found, use the default directory
      file_config_ = tmpString;
    else                          // Otherwise, split the directory name and the file name
    {
      dir_configFiles_ = tmpString.substr( 0, found );
      file_config_     = tmpString.substr( found+1 );
    }
  }
  else if ( argc - argIndex == 2 )  // Two input arguments.
  {                                 // Assume the config file and directory for trace files are given.
	// The first input argument
    tmpString        = argv[ argIndex ];
    found            = tmpString.find_last_of("/\\");  // This should work both for linux and windows.

    if ( found == string::npos )  // If no separator, e.g. "/", found, use the default directory
      file_config_ = tmpString;
    else                          // Otherwise, split the directory name and the file name
    {
      dir_configFiles_        = tmpString.substr( 0, found );
      file_config_            = tmpString.substr( found+1 );
      is_dir_configFiles_set_ = true;
    }
    ////////////////////////////////////////////////////////////////////////////
    dir_outputFiles_ = argv[ ++argIndex ];  // The second input argument
    is_dir_outputFiles_set_ = true;
  }
  else
  {
    cerr << "Error: Too many input arguments. Exiting..." << endl;
    exit(1);
  }
  cout << "  dir_configFiles_ = " << dir_configFiles_ << "\n"
	   << "  file_config_ = " << file_config_ << "\n"
       << "  dir_outputFiles_ = " << dir_outputFiles_ << "\n";
}

void
CommandLineArguments::ShowUsage()
{
  cout << " Usage\n"
	   << "   " << programName_ << " [config_file] [trace_file] [dir_trace_file] [dir_bin]\n"
       << "   config_file should be located in directory cfg_files.\n"
       << " Example\n"
       << "   " << programName_ << " default.cfg\n"
       << "   " << programName_ << " random-1-1-1.cfg"
//       << "   " << programName_ << " default.cfg \n"
       << endl;
}

void
CommandLineArguments::ShowVersionInformation()
{
  cout << " Neural Networks Simulator " << versionNumber_ << "\n"
       << "   released on " << releaseDate_ << " by Tae-Hyung \"T\" Kim\n";
}

void
CommandLineArguments::ShowDefaultMessage()
{
  cout << "Type " << programName_ << " -h for help." << endl;
}
