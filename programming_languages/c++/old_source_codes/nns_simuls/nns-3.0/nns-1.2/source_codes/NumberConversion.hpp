#ifndef __NUMBERCONVERSION_HPP_
#define __NUMBERCONVERSION_HPP_

#include   <iostream>
#include   <cassert>
#include   <cmath>
#include   <vector>

using namespace  std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<double> vdouble;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      NumberConversion
{
public:
           NumberConversion();

  void     test_ter2dec();
  double   ter2dec( double d2, double d1, double d0 );
  double   ter2dec( vdouble ternaryNumber );

  void     test_bin2dec();
  int      bin2dec( double* binary, int digits );
  void     dec2bin( double* binary, int digits, int decimal );

private:
  void     showBinary( double& binary, int numOfDigits );
  void     zeros( double* binary, int numOfDigits );
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
