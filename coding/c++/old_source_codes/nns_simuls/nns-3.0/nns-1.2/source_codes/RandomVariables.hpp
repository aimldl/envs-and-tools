#ifndef __RANDOMVARIABLES_HPP_
#define __RANDOMVARIABLES_HPP_

#include   <cstdlib>

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      RandomVariables
{
public:
	       RandomVariables();
  double   uniform();                           // R in [0,1]
  double   uniform( double min, double max );   // R in [min,max]
  int      uniformInteger( int min, int max );  // Z in [min,max]
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
