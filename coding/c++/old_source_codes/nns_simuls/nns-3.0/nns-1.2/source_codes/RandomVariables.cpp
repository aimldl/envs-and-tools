#include  "RandomVariables.hpp"
#include   <ctime>  // For time
#include   <cmath>  // For floor

// Definition of static variables

//==============================================================================
//                        Static Public functions
//==============================================================================

//==============================================================================
//                            Public functions
//==============================================================================

RandomVariables::RandomVariables()
{
  srand( time(NULL) );
}

double
RandomVariables::uniform()
{
  return ( static_cast<double> ( random() ) / static_cast<double> ( RAND_MAX ) );
}

double
RandomVariables::uniform( double min, double max )
{
  return ( (max-min) * uniform() + min );
}

// Note max+1 is used because temp is floored.

int
RandomVariables::uniformInteger( int min, int max )
{
  double temp;

  temp = uniform( static_cast<double> (min), static_cast<double> (max+1) );

  return floor(temp);
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
