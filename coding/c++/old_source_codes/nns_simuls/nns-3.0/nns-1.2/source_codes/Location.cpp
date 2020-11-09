#include  "Location.hpp"
#include  <iostream>

//==============================================================================
//                        Static Public functions
//==============================================================================
//==============================================================================
//                        Static Private functions
//==============================================================================
//==============================================================================
//                            Public functions
//==============================================================================

Location::Location()
{
}

Location::Location( int xx, int yy )
{
  x = xx;
  y = yy;
}

void
Location::show()
{
  cout << "x=" << x << " " << "y=" << y << endl;
}

void
Location::set( int xx, int yy )
{
  x = xx;
  y = yy;
}

Location
Location::operator+( Location op2 )
{
  Location temp;

  temp.x = x + op2.x;
  temp.y = y + op2.y;

  return temp;
}

Location
Location::operator-( Location op2 )
{
  Location temp;

  temp.x = x - op2.x;
  temp.y = y - op2.y;

  return temp;
}

Location
Location::operator=( Location op2 )
{
  x = op2.x;
  y = op2.y;

  return *this;
}

Location
Location::operator++( int incr )
{
  x++;
  y++;

  return *this;
}

Location
Location::operator--( int incr )
{
  x--;
  y--;

  return *this;
}

Location
Location::operator+=( Location op2 )
{
  x = x + op2.x;
  y = y + op2.y;

  return *this;
}

Location
Location::operator-=( Location op2 )
{
  x = x - op2.x;
  y = y - op2.y;

  return *this;
}

bool
Location::operator==( Location op2 )
{
  if ( ( op2.x==x ) && ( op2.y==y ) )
    return true;
  else
    return false;
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================
