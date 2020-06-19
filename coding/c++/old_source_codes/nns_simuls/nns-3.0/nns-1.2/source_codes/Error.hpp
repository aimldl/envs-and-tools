#ifndef __ERROR_HPP_
#define __ERROR_HPP_

#include  <cassert>
#include  <vector>

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                              Class Declaration
//==============================================================================

class     Error4Cell
{
public:
	      Error4Cell( int time_o, int time_i, double error );
	     ~Error4Cell();
  static  void    configure( const int maxEpochs_i );

  static  int     maxEpochs_i_;  // Keep this just in case

  int     time_o_;
  int     time_i_;
  double  error_;

};

class     Error4Cnn
{
public:
          Error4Cnn( int time_o, double systemError, vdouble aVectorOfCellError );
	  ~Error4Cnn();
  static  void    configure( const int numOfCells );

  static  int     numOfCells_;

  double  systemError_;
  vdouble aVectorOfCellError_;
  int     time_o_;
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
