#include  "TrainingAlgorithms.hpp"

// Definition of static variables
int
TrainingAlgorithms::maxEpochs_i_;

//==============================================================================
//                            Static functions
//==============================================================================

// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

// Design issue
//   Note configObj.get_psoObj_().get_maxEpochs_i_() is stored in two separate
//   classes (Pso and Cell). This value conceptually should be stored in
//   Pso, but is called in Cell all the time. In other words, Cell is the
//   placed where this value is called all the time in practice. On the other
//   hand, one may find this value in Pso. Because of the above reasons,
//   this value is stored both in Pso and Cell. Be careful, however, that
//   both values should be identical.

void
TrainingAlgorithms::configure( Config& configObj )
{
  assert( configObj.get_isConfigured_() );

  maxEpochs_i_  = configObj.get_cnnObj_().get_maxEpochs_i_();
}
// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================

TrainingAlgorithms::TrainingAlgorithms()
{
}

int
TrainingAlgorithms::get_maxEpochs_i_()
{
  return maxEpochs_i_;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

