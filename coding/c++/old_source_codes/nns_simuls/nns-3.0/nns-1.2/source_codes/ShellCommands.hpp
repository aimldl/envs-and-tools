#ifndef __SHELLCOMMANDS_HPP_
#define __SHELLCOMMANDS_HPP_

#include  <cassert>
#include  <cstdlib>
#include  <iostream>
#include  <unistd.h>  // For getcwd. Not from the standard C/C++ library.

using namespace std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ShellCommands
{
public:
	       ShellCommands( string initialCommand );
  void     display_cwd();
  string   get_cwd_() const;

private:
  void     set_cwd_();

  string  cwd_;  // current working directory
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
