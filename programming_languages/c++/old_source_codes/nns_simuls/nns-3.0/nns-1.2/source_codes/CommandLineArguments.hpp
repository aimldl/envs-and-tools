#ifndef  __COMMANDLINEARGUMENTS_HPP_
#define  __COMMANDLINEARGUMENTS_HPP_

#include  <iostream>
#include  <cassert>
#include  <cstdlib>

#include  "GetOpt.hpp"
#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      CommandLineArguments : public Myiostream
{
public:
           CommandLineArguments( int argc, char* argv[] );
          ~CommandLineArguments();

private:
  void     process( int argc, char* argv[] );
  void     processCommandLineOptions( GetOpt& getopt );
  void     processFileNames( GetOpt& getopt );
      
  void     ShowUsage();
  void     ShowVersionInformation();
  void     ShowDefaultMessage();

  string   programName_;
  string   releaseDate_;
  string   versionNumber_;
};

#endif
//==============================================================================
//                                  Comments
//==============================================================================

//         GetOpt library is used to process command line options.
//         The GetOpt library files are GetOpt.{cpp, hpp}
//
// Usage:
//   CommandLineArguments* cmdLineArgsObj_p
//                       = new CommandLineArguments( argc, argv );
//     or
//   CommandLineArguments* cmdLineArgsObj_p = new CommandLineArguments;
//   cmdLineArgsObj_p->process( argc, argv );

