#ifndef  __CONFIGNEURALNETWORKS_HPP_
#define  __CONFIGNEURALNETWORKS_HPP_

#include  <string>
#include  <cassert>
#include  <iostream>
#include  <fstream>  // For ifstream
#include  <cstdlib>  // for exit

#include  "MyStringUtilFunctions.hpp"  // For str2ints
#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<int> vint;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     ConfigNeuralNetworks : public Myiostream
{
public:
          ConfigNeuralNetworks();
         ~ConfigNeuralNetworks();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                   int& validValueFlag, int& alreadyFoundFlag);
  string  get_numOfNeuronsInLayers_() const;
  string  get_activationFunctionHiddenLayer_() const;
  string  get_activationFunctionOutputLayer_() const;
  int     get_totalNumOfLayers_() const;
  vint    get_numOfNeuronsInLayersVector_() const;
  int     get_activationFunction_() const;
  double  get_slopeParamLogsig_() const;
  double  get_slopeParamTansig_() const;
  double  get_ternaryStepFn_c_() const;
  double  get_ternaryStepFn_w_() const;
      
private:
  void    validate_typeOfActivationFunction( string stringInConfigFile, string activationFunction );
  vint    process_numOfNeuronsInLayers_( string numOfNeuronsInLayers );

  int     activationFunction_;
  double  slopeParamLogsig_;
  double  slopeParamTansig_;
  double  ternaryStepFn_c_;
  double  ternaryStepFn_w_;
  vint    numOfNeuronsInLayersVector_;
  int     totalNumOfLayers_;
  string  numOfNeuronsInLayers_;
  string  activationFunctionHiddenLayer_;
  string  activationFunctionOutputLayer_;

  bool    activationFunction_found_;
  bool    activationFunctionHiddenLayer_found_;
  bool    activationFunctionOutputLayer_found_;
  bool    slopeParamLogsig_found_;
  bool    slopeParamTansig_found_;
  bool    numOfNeuronsInLayers_found_;
  bool    ternaryStepFn_c_found_;
  bool    ternaryStepFn_w_found_;

  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// Note our convention is TotalNumOfLayers = numOfHiddenLayers_+2.
// In this file, we implicitly imply TotalNumOfLayers by setting "numOfHiddenLayers_+2".
// We don't set
//
//   const int TotalNumOfLayers = numOfHiddenLayers_ + 2;
//
//   because TotalNumOfLayers is used only a few times in this file.
//
// In class NeuralNetworks, however, totalNumOfLayers_ is explicitly set in
//   its member function configure(...) to enhance readability of source codes. That is,
//
//     totalNumOfLayers_ = numHiddenLayers_ + 2;
//
// Reason why numOfHiddenLayers_ is used instead of TotalNumOfLayers is because
//   there exists two different conventions for TotalNumOfLayers.
//   Some people include the output layer to count TotalNumOfLayers. That is,
//
//     TotalNumOfLayers = numOfHiddenLayers_+2 for some people,
//
//   The others exclude the output layer, so
//
//    TotalNumOfLayers = numOfHiddenLayers_+1
//
//   Both conventions have numOfHiddenLayers_, so we use numOfHiddenLayers_ to avoid confusion.
//   As state, we follow the first convention.

