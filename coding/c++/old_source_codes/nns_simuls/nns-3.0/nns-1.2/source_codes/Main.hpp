#ifndef  __MAIN_HPP_
#define  __MAIN_HPP_

// For CSRN
#include  "ApiGnuplot.hpp"
#include  "ApiPostprocess.hpp"
#include  "BadukData.hpp"
#include  "Cnn.hpp"
#include  "CommandLineArguments.hpp"
#include  "Config.hpp"
#include  "ShellCommands.hpp"
#include  "Myiostream.hpp"

// For reinforcement learning
#include  "GridWorld.hpp"
#include  "ReinforcementLearning.hpp"
#include  "CliffWalkingProblem.hpp"
#include  "RLGoEngine.hpp"

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// The following lines set the standard input to a trace file.
// In other words, cout outputs a message or string to the trace file,
// not to the console output or computer monitor.
// Use cerr to print out a message to the console.
//
//  ofstream                outputObj;
//    streambuf*              streambuffer;
//
//  string                  traceFileWithFullPath;
//  traceFileWithFullPath = configObj_p->get_traceFileWithFullPath_();
//
//  cout << "    Standard output will be saved to '" << traceFileWithFullPath;
//  cout << "'." << endl;
//  outputObj.open( traceFileWithFullPath.c_str() );
//  streambuffer = outputObj.rdbuf();
//  cout.rdbuf( streambuffer );

// The following line to use scientific precision is less likely to be used in the future.
// But keep these lines just in case.
/*
//#include   <iomanip>    // For setprecision

    // FOR DEBUGGING
    //   Using scientific to find a bug. 5.8e-270 appears as 0 if cout is used.
    //   So the code may work unexpectedly.
    double dummy (0.12345);

    cout << "#\tUse 'cout << setprecision(1) << scientific' for debugging."
         << endl;
    cout << "#\tA number in double will be displayed as follows." << endl;
    cout << "#\t" << dummy << "==>"
         << setprecision(1) << scientific << dummy << endl;
    cout << "#\tNote this formatting doesn't affect integers." << endl;
    cout << endl;
    // FOR DEBUGGING
*/


// Comment on Part 1. Process command-line arguments & configuration
//
//   This part prepares the rest of the program by processing the command line
// arguments and the configuration file (a text file). The default config file
// is default.cfg. It is suggested to override the default config file when
// you run this program because it's convenient to run it many times.
//   Currently, the command line arguments don't do much other than reading
// the specified config file name because this program is designed to
// configure simulation settings in a config file.
//   Reading the configuration file is nothing but mapping parameters/values
// in the config file to member variables in the target classes. For example,
// "simul_task_type = test_problem" in default.cfg is mapped to a variable
// ConfigSimulations::taskType_ in ConfigSimulations.hpp. Note this mapping
// is done in the next part.
//
// Design principle:
//   Correctness of the values read from a config file should be validated
//   in class Config and its derived classes. In this way, the
//   subsequent part of the program assumes those values are correct and
//   do not include lines to check errors. Moreover, it is logical to remove
//   an error caused by a config file when the file is processed. It helps
//   for debugging as well.
//
// Comment on Part 2. Configure classes
//   Configuring classes means that values in a configuration file are mapped
// to static variables in classes.
//
// Comment on Part 3. Main part
//   Step 1. Prepare the input & target data.
//   Step 2. Instantiate & initialize classes.
//   Step 3. Run simulations.
//
//   Design issue:
//     Class Csrn or Cmlp is unneccesary because Class Cnn uses Class Cell.
//     The cellular architecture level, only sees cells.
//     Just specify the cell type.

