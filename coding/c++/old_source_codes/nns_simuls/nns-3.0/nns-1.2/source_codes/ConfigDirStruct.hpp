#ifndef  __CONFIGDIRSTRUCT_HPP_
#define  __CONFIGDIRSTRUCT_HPP_

#include  <cassert>
#include  <cstdlib>  // For exit
#include  <fstream>  // For ifstream
#include  <iostream>
#include  <string>

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     ConfigDirStruct : public Myiostream
{
public:
          ConfigDirStruct();
         ~ConfigDirStruct();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                   int& validValueFlag, int& alreadyFoundFlag);
  string  get_dirGnuplotConfigFile_() const;
  string  get_fileNnWeights_() const;
  string  get_fileNnInitialWeights_() const;

  bool    get_fileNnWeights_found_() const;
  bool    get_fileNnInitialWeights_found_() const;
  bool    get_dirGnuplotConfigFile_found_() const;

  string  get_file_gnuplotInput_() const;
  string  get_file_gnuplotConfig_() const;
  string  get_file_gnuplotOutput_() const;
  bool    get_file_gnuplotConfig_found_() const;
  bool    get_file_gnuplotInput_found_() const;
  bool    get_file_gnuplotOutput_found_() const;

private:
  string  dirGnuplotConfigFile_;
  string  fileNnInitialWeights_;
  string  fileNnWeights_;
  string  fileGnuplotInput_;
  string  fileGnuplotOutput_;

  string  file_gnuplotInput_;
  string  file_gnuplotConfig_;
  string  file_gnuplotOutput_;


  bool    dirGnuplotConfigFile_found_;
  bool    fileNnInitialWeights_found_;
  bool    fileNnWeights_found_;
  bool    fileGnuplotInput_found_;
  bool    fileGnuplotOutput_found_;

  bool    file_gnuplotInput_found_;
  bool    file_gnuplotConfig_found_;
  bool    file_gnuplotOutput_found_;

  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// Note dirConfigFiles_ is missing here.
// dirConfigFiles_ should be hard-coded in class Config
// because the path should be set in order to read a configuration file.
// If dirConfigFiles_ is set in a configuration file, the config file
// cannot be read!
