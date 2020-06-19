#ifndef  __CONFIGURATION_HPP_
#define  __CONFIGURATION_HPP_

#include  <fstream>
#include  <cassert>
#include  <cctype>  // For int isspace( ... )
#include  <string>  // For stricmp( ... )

#include  "Myiostream.hpp"

// ADD CLASS WITH NEW CONFIGURATION PARAMETERS
#include  "ConfigSimulations.hpp"
#include  "ConfigDirStruct.hpp"
#include  "ConfigData.hpp"
#include  "ConfigNeuralNetworks.hpp"
#include  "ConfigPso.hpp"
#include  "ConfigGnuPlot.hpp"
#include  "ConfigCnn.hpp"
#include  "ConfigReinLearning.hpp"
// ADD CLASS WITH NEW CONFIGURATION PARAMETERS

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     Config : public Myiostream
{
public:
          Config( const string& cwd );
         ~Config();

  void    close_configFile();
  bool    get_isConfigured_() const;

  ConfigSimulations     get_simulationsObj_() const;
  ConfigDirStruct       get_dirStructObj_() const;
  ConfigData            get_dataObj_() const;
  ConfigNeuralNetworks  get_neuralNetsObj_() const;
  ConfigPso             get_psoObj_() const;
  ConfigGnuPlot         get_gnuPlotObj_() const;
  ConfigCnn             get_cnnObj_() const;
  ConfigReinLearning    get_rlObj_() const;

private:
  void    openConfigFile( const string fileConfigFileWithFullPath );
  void    openConfigFile( const string dir_root, const string dir_configFiles, const string file_config );
  void    processConfigClasses();

  static  bool          isConfigured_;
  ifstream              inputObj_;

  // CONFIGCLASSES WITH NEW CONFIGURATION PARAMETERS
  ConfigSimulations     simulationsObj_;
  ConfigDirStruct       dirStructObj_;
  ConfigData            dataObj_;
  ConfigNeuralNetworks  neuralNetsObj_;
  ConfigPso             psoObj_;
  ConfigGnuPlot         gnuPlotObj_;
  ConfigCnn             cnnObj_;
  ConfigReinLearning    rlObj_;
  // CONFIGCLASSES WITH NEW CONFIGURATION PARAMETERS
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
//   This class plays the central role to process the configuration parameters
// in a config file, e.g. default.cfg in directory ../config_files.
// Instantiate this class to process the configuration parameters.
//   The key function is processConfigClasses() which processes configuration
// parameters (ConfigParams) in configuration Classes (ConfigClass).
// For example, the following lines invokes a public function in an instance of
// class ConfigCnn cnnObj_ which will process the relevant parameters defined in
// the class.
//
//    if
//    (
//      cnnObj_->process
//      (
//        name,
//        inputObj_,
//        validNameFlag,
//        validValueFlag,
//        alreadyFoundFlag
//      )
//    )
//    {
//      goto bookmark;
//    }
//
//
//   Just to clarify two terms (ConfigClass and ConfigParams) are explained
// below. The former refers to a class that holds a group of similar
// ConfigParams. For example, a derived class of ConfigCnn holds configuration
// parameters related to class Cnn.
//   The latter refers to a configuration parameter, e.g. cnn_max_epoch_o in
// ConfigCnn. Note a ConfigParam is tested for the following basic data type:
// char, bool, int, and string. Using a string type data as a dummy variable can
// be useful to read an array of data, but this idea has not been tested yet.
//   While class Config can process a ConfigParam in the config file,
// it is strongly suggested to use a ConfigClass for a new group of ConfigParams.
//
//   Note that ConfigGnuPlot does not inherit Config. An infinite loop
// was created when ConfigGnuPlot is instantiated. This loop does not invoke
// compilation error, but segfault when the program is executed.
//
//   void
//   Config::newConfigClasses()
//   {
//    gnuPlotObj_ = new ConfigGnuPlot;
//   }
//
//   Error:
//     Set .0 ...        Error: Unknown variable name '.0'
//   Maybe wrong type. For example, double type variable is declared as int.
//
//   The infinite loop is created as follows. In newConfigClasses(), new
// ConfigGnuPlot will call the constructor of Config when Config
// is inherited by ConfigGnuPlot. In the constructor newConfigClasses() is
// called again. I think this can be fixed with a little bit of efforts, but
// leave it as an example to work around an infinite loop.
//
// Design issue:
//   Use of define can reduce the file size of the source codes. However, I
// prefer not to do so because it will dramatically reduce readability of the
// source codes.
