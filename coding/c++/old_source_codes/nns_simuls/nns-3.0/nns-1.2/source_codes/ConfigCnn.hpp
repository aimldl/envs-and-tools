#ifndef  __CONFIGCNN_HPP_
#define  __CONFIGCNN_HPP_

#include  <fstream>
#include  <iostream>
#include  <string>
#include  <cstdlib>  // for exit

#include  "Myiostream.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      ConfigCnn : public Myiostream
{
public:
           ConfigCnn();
          ~ConfigCnn();
  bool    process( const char* name, ifstream& inputObj, int& validNameFlag,
                   int& validValueFlag, int& alreadyFoundFlag);

  int     get_maxEpoch_o_() const;
  int     get_maxEpochs_i_() const;
  double  get_targetSystemError_() const;
  double  get_targetCellError_() const;
  string  get_fdInputInitialization_() const;
  string  get_errorMetric_() const;
  string  get_nnType_() const;
  string  get_trainingAlgorithm_() const;
  bool    get_matchNnInitialWeightsToTrainingAlgo_() const;
  string  get_initialWeightsMode_() const;

private:
  void    validate_fdInputInitialization_();
  void    validate_errorMetric_();
  void    validate_trainingAlgorithm_();
  void    validate_nnType_();
  void    validate_matchNnInitialWeightsToTrainingAlgo_();
  void    validate_initialWeightsMode_();

  int     maxEpoch_o_;
  int     maxEpochs_i_;
  double  targetSystemError_;
  double  targetCellError_;
  string  fdInputInitialization_;
  string  errorMetric_;
  string  trainingAlgorithm_;
  string  nnType_;
  bool    matchNnInitialWeightsToTrainingAlgo_;
  string  initialWeightsMode_;

  bool    maxEpoch_o_found_;
  bool    maxEpochs_i_found_;
  bool    targetSystemError_found_;
  bool    targetCellError_found_;
  bool    fdInputInitialization_found_;
  bool    errorMetric_found_;
  bool    trainingAlgorithm_found_;
  bool    nnType_found_;
  bool    matchNnInitialWeightsToTrainingAlgo_found_;
  bool    initialWeightsMode_found_;

  bool    isGotoBookmark_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// This class is to configure simulations.
