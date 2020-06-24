#include  "ApiGnuplot.hpp"

//==============================================================================
//                            Static functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

// systemCommandRunGnuplot_ will look someting like "gnuplot example.gp"
// gnuplotConfigFile_ should be specified from gnuplotConfigFile_.
// systemCommandRunGnugv_ will look someting like "gv default.ps"

ApiGnuplot::ApiGnuplot()
{
  gnuplotCommand_.assign( "gnuplot" );

  systemCommandRunGnuplot_ = gnuplotCommand_ + " " + file_gnuplotConfig_with_path_;
  systemCommandRunGnugv_   = "gv " + gnuplotOutputFileWithFullPath_;

  cout << "  ApiGnuplot::systemCommandRunGnuplot_ = '"  << systemCommandRunGnuplot_ << "'" <<endl;
  cout << "  ApiGnuplot::systemCommandRunGnugv_ = '" << systemCommandRunGnugv_ << "'" <<endl;
}

ApiGnuplot::~ApiGnuplot()
{
}

void
ApiGnuplot::run()
{
  int flag;
  
  flag = system( systemCommandRunGnuplot_.c_str() );
  
  if ( flag )  // If flag is a non-zero value, something's wrong.
  {
    cout << "  " << systemCommandRunGnuplot_.c_str() << " failed.\n"
         << "  Non-zero value (" << flag << ") is returned. \n"
         << "  Possible causes for this error include: \n"
         << "    1. GNU Plot is not installed, \n"
         << "    2. GNU Plot configuration file name (*.gp) is incorrect, \n"
         << "    3. GNU Plot execution failed. " << endl;
    exit( 1 );
  }
  else
  {
	cout << "  GNU Plot is successfully launched. " << endl;
	cout << "    Use a command gv to check a postscript file (*.ps). " << endl;

    flag = system ( systemCommandRunGnugv_.c_str() );
    if ( flag )  // If flag is a non-zero value, something's wrong.
    {
      cout << "  " << systemCommandRunGnugv_.c_str() << " failed.\n"
           << "  Non-zero value (" << flag << ") is returned. \n"
           << "  Possible causes for this error include: \n"
           << "    1. GNU gv is not installed, \n"
           << "    2. GNU gv input file name, e.g. *.ps, is incorrect, \n"
           << "    3. GNU gv execution failed. " << endl;

      exit( 1 );
    }
    else
    {
      cout << "  GNU Ghostview is successfully launched. " << endl;
    }
  }
 
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
