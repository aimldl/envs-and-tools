#ifndef  __TRAININGALGORITHMS_HPP_
#define  __TRAININGALGORITHMS_HPP_

#include  "SimObject.hpp"

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      TrainingAlgorithms: public SimObject
{
public:
           TrainingAlgorithms();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  static
  int      get_maxEpochs_i_();

protected:
  static
  int      maxEpochs_i_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
