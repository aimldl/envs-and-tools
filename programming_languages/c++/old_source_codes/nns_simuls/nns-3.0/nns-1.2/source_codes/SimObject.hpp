#ifndef  __SIMOBJECT_HPP_
#define  __SIMOBJECT_HPP_

#include   <cmath>  // For function exp( ... )
#include   <cstring>
#include   <vector>

#include  "Config.hpp"
#include  "Myiostream.hpp"

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                              Class Declaration
//==============================================================================
class     SimObject : public Myiostream
{
public:
          SimObject();
         ~SimObject();

protected:
  static  int      time_o_;  // epoch for outer lopp
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// Class SimObject is a parent class for several classes.
// The reason is these classes share certain variables and setting those
// variables is totally redudant.
//   If there is a variable shared by several classes and you don't know which
// class is the best to declare the variable, SimObject may be a safe place to
// start with if those classes inherit SimObject.
//   Note, however, that declaring a variable in SimObject can be far from optimal
// because this variable is shared by manu classes inherit SimObject.
