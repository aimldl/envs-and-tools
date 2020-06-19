#ifndef  __LOCATION_HPP_
#define  __LOCATION_HPP_

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
//==============================================================================
//                            Structure Declaration
//==============================================================================

struct     Location
{
	       Location();
	       Location( int xx, int yy );
  int x;
  int y;

  void     show();
  void     set( int xx, int yy );

  Location operator+( Location op2 );
  Location operator-( Location op2 );
  Location operator=( Location op2 );
  Location operator++( int incr );
  Location operator--( int incr );
  Location operator+=( Location op2 );
  Location operator-=( Location op2 );
  bool     operator==( Location op2 );  // is identical?
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================
//
// This is a structure for a location in Catesian coordinate.
// The advantage of using this structure over a simple int x & int y approach is
// because of the operator overloading defined at the bottom of the structure.
// In other words,
//
//   Location operator+( Location op2 );
//   Location operator-( Location op2 );
//   Location operator=( Location op2 );
//   Location operator++( int incr );
//   Location operator--( int incr );
//   Location operator+=( Location op2 );
//   Location operator-=( Location op2 );
//
// One may use int x and int y instead of this structure, but cannot use the overloaded
// operators.
