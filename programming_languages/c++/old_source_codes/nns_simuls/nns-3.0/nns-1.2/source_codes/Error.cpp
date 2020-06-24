#include  "Error.hpp"

int    Error4Cell::maxEpochs_i_;
int    Error4Cnn::numOfCells_;

//==============================================================================
//                        Static Public functions
//==============================================================================

void
Error4Cell::configure( const int maxEpochs_i )
{
  assert( maxEpochs_i > 0 );

  maxEpochs_i_ = maxEpochs_i;
}

void
Error4Cnn::configure( const int numOfCells )
{
  assert( numOfCells > 0 );

  numOfCells_ = numOfCells;
}

//==============================================================================
//                        Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

Error4Cell::Error4Cell( int time_o, int time_i, double error )
{
  time_o_ = time_o;
  time_i_ = time_i;
  error_  = error;
}

Error4Cell::~Error4Cell()
{
}

Error4Cnn::Error4Cnn( int time_o, double systemError, vdouble aVectorOfCellError )
{
  time_o_             = time_o;
  systemError_        = systemError;
  aVectorOfCellError_ = aVectorOfCellError;
}

Error4Cnn::~Error4Cnn()
{
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================
