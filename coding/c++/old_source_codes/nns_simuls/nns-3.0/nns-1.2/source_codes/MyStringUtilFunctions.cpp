#include  "MyStringUtilFunctions.hpp"
#include  <cstring>  // for size_t
#include  <cstdlib>  // for atoi, atof

//==============================================================================
//                        Static Public functions
//==============================================================================

////////////////////////////////////////////////////////////////////////////////
//               Functions to convert a string to double
////////////////////////////////////////////////////////////////////////////////
// str2double converts a string to a double-type variable
// str2doubles is for a multiple of double-type variables.

double
MyStringUtilFunctions::str2double( const string & str )
{
  assert( !str.empty() );

  stringstream ss( str );
  double n;
  ss >> n;
  return n;
}

vdouble
MyStringUtilFunctions::str2doubles( const string & str )
{
  assert( !str.empty() );

  int     location ( 0 );             // delimiter's location
  int     substrLength ( 0 );
  double  tmpValue;                   // Dummy variables make debugging easier &
  string  tmpSubstr;                  // enhance code readability!
  string  tmpStr;                     // str is const, so use a dummy string.
  vdouble doublesVector;

  tmpStr = str;

  while ( !tmpStr.empty() )           // true if the string is empty.
  {
    location = tmpStr.find( ":", 0 ); // Find the first delimiter location.

    if ( location != string::npos )   // If the delimiter is found, extract
    {                                 // a substring before the delimiter.
      tmpSubstr = tmpStr.substr( 0, location );  // Delimiter not included.
      tmpValue = str2double( tmpSubstr );
      tmpStr.erase( 0, location+1 );  // Erase including the delimiter.
    }
    else                              // If no delimiter is found, tmpStr is the
    {                                 // last substring.
      tmpValue = str2double( tmpStr );
      tmpStr.clear();                 // Clear the string to end the while loop.
    }
    doublesVector.push_back( tmpValue );
//  cout << tmpValue << endl;
  }
  return doublesVector;
}

////////////////////////////////////////////////////////////////////////////////
//               Functions to convert a string to int
////////////////////////////////////////////////////////////////////////////////
// str2int converts a string to a integer-type variable
// str2ints is for a multiple of integer-type variables.

int
MyStringUtilFunctions::str2int( const string & str )
{
  assert( !str.empty() );

  stringstream ss( str );
  int n;
  ss >> n;
  return n;
}

vint
MyStringUtilFunctions::str2ints( const string & str )
{
  assert( !str.empty() );

  int     location ( 0 );             // delimiter's location
  int     substrLength ( 0 );
  int     tmpValue;                   // Dummy variables make debugging easier &
  string  tmpSubstr;                  // enhance code readability!
  string  tmpStr;                     // str is const, so use a dummy string.
  vint    intsVector;

  tmpStr = str;

  while ( !tmpStr.empty() )           // true if the string is empty.
  {
    location = tmpStr.find( ":", 0 ); // Find the first delimiter location.

    if ( location != string::npos )   // If the delimiter is found, extract
    {                                 // a substring before the delimiter.
      tmpSubstr = tmpStr.substr( 0, location );  // Delimiter not included.
      tmpValue = str2int( tmpSubstr );
      tmpStr.erase( 0, location+1 );  // Erase including the delimiter.
    }
    else                              // If no delimiter is found, tmpStr is the
    {                                 // last substring.
      tmpValue = str2int( tmpStr );
      tmpStr.clear();                 // Clear the string to end the while loop.
    }
    intsVector.push_back( tmpValue );
//  cout << tmpValue << endl;
  }
  return intsVector;
}

// Count the number of ":" or countColumn in tmpString.
int
MyStringUtilFunctions::countNumberOfColumnsIn( string tmpString )
{
  size_t pos;
  string dummy = tmpString;
  string dummySubstr;
  int    countColumn = 0;

  pos = dummy.find( ":" );
  while ( pos!=string::npos )  // Loop through while ":" is found.
  {
    countColumn++;
    // Swap dummySubstr with dummy
    dummySubstr = dummy.substr( pos+1 );
    dummy       = dummySubstr;
    pos         = dummy.find( ":" );
  }
//  cout << countColumn << " ':'s are found" << endl;
  return countColumn;
}

// This function is tested on a string with numberOfColumns=1, 2, 3, 4, 5.
// So I assume it works for all size of numberOfColumns.
//
// Example of tmpString: -1:-100. No space is assumed around ":"
//   reward_ = -1; penalty_ = -100;
// Example of tmpString: 100:--1:-100:. No space is assumed around ":"
//   reward_ = -1; penalty_ = -100;

vdouble
MyStringUtilFunctions::separateSubstringsByColumns( string tmpString )
{
  size_t  pos;
  string  dummy;
  string  dummySubstr;
  vdouble outputVector;
  double  temp;
  int     numberOfColumns = 0;

  numberOfColumns = countNumberOfColumnsIn( tmpString );
  assert( numberOfColumns > 0 );

  dummy = tmpString;
  for ( int n=0; n<numberOfColumns+1; n++)  // number of substrings = numberOfColumns+1
  {
    pos         = dummy.find( ":" );
    temp        = atof( dummy.substr( 0, pos ).c_str() );
    outputVector.push_back( temp );
    dummySubstr = dummy.substr( pos+1 );
    dummy       = dummySubstr;
  }

//  for ( int n=0; n<numberOfColumns+1; n++)  // number of substrings = numberOfColumns+1
//    cout << "outputVector.at(" << n << ")="<<outputVector.at( n ) << endl;

  return outputVector;
}


//==============================================================================
//                            Public functions
//==============================================================================

MyStringUtilFunctions::MyStringUtilFunctions()
{
}

string
MyStringUtilFunctions::appendStrings( const string fullPath, const string fileName )
{
  assert( !fullPath.empty() );
  assert( !fileName.empty() );

  string fileNameWithFullPath;

  fileNameWithFullPath = fullPath + "/" + fileName;
  return fileNameWithFullPath;
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
