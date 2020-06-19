#ifndef  __MYSTRINGUTILFUNCTIONS_HPP_
#define  __MYSTRINGUTILFUNCTIONS_HPP_

#include  <cassert>
#include  <iostream>
#include  <sstream>
#include  <vector>

using namespace  std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector <double> vdouble;
typedef vector <int>    vint;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      MyStringUtilFunctions
{
public:
           MyStringUtilFunctions();
  static
  double   str2double( const string & str );
  static
  vdouble  str2doubles( const string & str );
  static
  int      str2int( const string & str );
  static
  vint     str2ints( const string & str );
  static
  int      countNumberOfColumnsIn( string tmpString );
  static
  vdouble  separateSubstringsByColumns( string tmpString );

  string  appendStrings( const string fullPath, const string fileName);
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
