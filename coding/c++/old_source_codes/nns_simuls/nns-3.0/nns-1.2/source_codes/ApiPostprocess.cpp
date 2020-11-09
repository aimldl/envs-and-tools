#include  "ApiPostprocess.hpp"

//==============================================================================
//                            Static functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

ApiPostprocess::ApiPostprocess()
{
  // This is used to create a system command.
  // nns_postprocess is a bash script stored in directory bin.
  postprocessCommand_.assign( "nns_postprocess" );
}

ApiPostprocess::~ApiPostprocess()
{
}

void
ApiPostprocess::run()
{
  // This string shouldn't be empty.
  assert( ! postprocessCommand_.empty() );

  int flag;

  // systemCommandRunPostprocess_ will look someting like
  // "nns_postprocess default.out".

  // TODO: Change "./" to the directory where nns_dbg.exe is stored.
  //       Running the command in Eclipse will cause an error because the
  //       directory for Eclipse is different from where nns_dbg.exe is located.

  // Assume PATH to directory bin has been already set.
  //
  if ( dir_bin_.empty() )
    systemCommandRunPostprocess_ = postprocessCommand_ + " " + file_trace_with_path_;
  else
	systemCommandRunPostprocess_ = dir_bin_ + "/" + postprocessCommand_ + " " + file_trace_with_path_;

  assert( !systemCommandRunPostprocess_.empty() );

  cerr << "  Postprocessing " << file_trace_with_path_ << "...\n";
  cerr << "  $ " << systemCommandRunPostprocess_ << endl;

  flag = system( systemCommandRunPostprocess_.c_str() );

  if ( flag )  // If flag is a non-zero value, something's wrong.
  {
    cout << "  " << systemCommandRunPostprocess_.c_str() << " failed."
         << endl;
    cout << "  Non-zero value (" << flag << ") is returned."
         << endl;
    exit( 1 );
  }
  else
  {
    cout << "  " << postprocessCommand_ << " is successfully launched."
         << endl;
  }
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
