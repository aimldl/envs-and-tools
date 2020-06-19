#include  "ShellCommands.hpp"

// Definition of static variables

//==============================================================================
//                        Static Public functions
//==============================================================================

//==============================================================================
//                            Public functions
//==============================================================================

ShellCommands::ShellCommands( string initialCommand )
{
  assert( !initialCommand.empty() );

  if ( initialCommand == "display_cwd" )
    display_cwd();
  else if ( initialCommand == "set_cwd" )
    set_cwd_();
  else
  {
    cerr << "Nothing is defined for a command " << initialCommand << endl;
    exit(1);
  }
}

void
ShellCommands::display_cwd()
{
  if ( cwd_.empty() )
    set_cwd_();

  cout << "Current working directory = \"" << cwd_ << "\"" << endl;
}

string
ShellCommands::get_cwd_() const
{
  return cwd_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
ShellCommands::set_cwd_()
{
  char tmpCwd[256];
  cwd_ = getcwd( tmpCwd, 256 );  // Note getcwd is not in the standard C/C++ library.
}
