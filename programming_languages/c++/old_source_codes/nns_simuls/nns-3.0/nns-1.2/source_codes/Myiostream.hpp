#ifndef __MYIOSTREAM_HPP_
#define __MYIOSTREAM_HPP_

#include   <cassert>
#include   <cstdlib>  // exit,
#include   <fstream>
#include   <iomanip>  // for setw (class Pso)
#include   <iostream>
#include   <string>

using namespace std;

//==============================================================================
//                             Forward Declaration
//==============================================================================
class      Config;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      Myiostream
{
public:
	       Myiostream();
	      ~Myiostream();

  static   void     setDefaultValues();
  static   void     configure( Config& configObj );
  static   void     closeAllIosInstances( const int numOfCells );

  string   get_dir_outputFiles_() const;
  string   get_dir_configFiles_() const;
  string   get_dir_bin_() const;
  string   get_file_config_() const;
  string   get_file_trace_() const;
  string   get_file_debug_() const;
  bool     get_isDefaultValuesSet_() const;
  string   extract_dir_root_( const string cwd );

protected:
  static   string    appendStrings( const string dir_target, const string filename );
  static   string    appendStrings( const string dir_root, const string dir_target, const string filename );
  static   void      updateFileNamesWithPathForCnn();
  static   void      updateFileNamesWithPath();

  static   ofstream  nout_init; // For neural network initial weights
  static   ifstream  nin_init;  // Previously, inputObjNnWeights_. Dual with nout.
  static   ofstream  nout;      // neural networks out
  static   ofstream  eout;      // Previously, outputObjErrorProfile_. Error profile out
  static   ofstream  tout;      // trace out
  static   ofstream  pout;      // GNU plot output
  static   ofstream  dout;      // trace for debugging
  static   ofstream* lout;      // Cell output

  static   bool      trace4dbg_;
  static   bool      isDefaultValuesSet_;
  static   bool      is_dir_outputFiles_set_;
  static   bool      is_dir_configFiles_set_;
  static   string    initialWeightsMode_;

  static   string    dir_root_;
  static   string    dir_outputFiles_;
  static   string    dir_configFiles_;
  static   string    dir_bin_;
  static   string    file_config_;
  static   string    file_trace_;
  static   string    file_debug_;
  static   string    file_nnWeights_;
  static   string    file_nnInitialWeights_;
  static   string    file_ErrorProfile_;

  static   string    dir_gnuplotConfigFile_;
  static   string    file_gnuplotConfig_;

  static   string    file_gnuplotInput_;
  static   string    gnuplotInputFileWithFullPath_;
  static   string    file_gnuplotOutput_;
  static   string    gnuplotOutputFileWithFullPath_;  // An example of the former is gnuplot_test_output.ps.

  static   string    file_config_with_path_;
  static   string    file_trace_with_path_;
  static   string    file_debug_with_path_;
  static   string    file_nnWeights_with_path_;
  static   string    file_nnInitialWeights_with_path_;
  static   string    file_ErrorProfile_with_path_;
  static   string    file_gnuplotConfig_with_path_;

private:
  static
  void     set_nout_init_or_nin_init( string fileNnInitialWeightsWithFullPath, string initialWeightsMode );
  static
  void     set_nout( string fileNnWeightsWithFullPath_ );
  static
  void     set_tout( string fileTraceWithFullPath );
  static
  void     set_dout( string fileDebugWithFullPath );
  static
  void     set_pout( string fileGnuplotConfigFileWithFullPath );
  static
  void     set_eout( string fileErrorProfileWithFullPath );
  static
  void     set_lout( const string dir_outputFiles, const int numOfCells );

  static
  bool     is_lout_set_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// Note class Myiostream is designed to be instantiated just once.
// The file streams, e.g. nout, should be static. Otherwise, the files are not saved in the
// same file because child classes creates a new variable whenever it's instantiated.
