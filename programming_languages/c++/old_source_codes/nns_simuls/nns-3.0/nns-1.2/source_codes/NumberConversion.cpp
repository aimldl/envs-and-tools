#include  "NumberConversion.hpp"

// Definition of static variables

//==============================================================================
//                        Static Public functions
//==============================================================================

//==============================================================================
//                            Public functions
//==============================================================================

NumberConversion::NumberConversion()
{
}

// test_ter2dec()
//   Test a function ter2dec() for input dimension reduction for CSRN
//   The input dimension reduction is a technique proposed by me to reduce
//   the complexity of the search domain.
//     Each input to MLP has a value ranging from zero to two. In other words,
//   the input is a ternary number. Three inputs are grouped together in order
//   to make a three digit ternary number. Because MLP typically takes a floating
//   number input, the three digit ternary number is converted to a decimal number.
//   In this manner, the three MLP input in ternary can be reduced to a single MLP
//   input in decimal.
//     In this function, ternary numbers ranging from 000 to 222 are converted to
//   the corresponding decimal numbers from 0 to 26.

/*
void
NumberConversion::test_ter2dec()
{
  double  decimalNumber;
  int     numberOfDigits;
  vdouble ternaryNumber;

  numberOfDigits = 3;  // We test a case for only three digits here.

  // ternaryNumber has three bins and they are changed from 000 to 222.
  for ( double t2 = 0.0; t2 < numberOfDigits; t2+=1.0 )
  {
    for ( double t1 = 0.0; t1 < numberOfDigits; t1+=1.0 )
    {
      for ( double t0 = 0.0; t0 < numberOfDigits; t0+=1.0 )
      {
    	// Push back adds a number from left to right, so t2 should be
    	// inserted to the vector first. In other words,
    	// ternaryNumber has t2 t1 t0. For example,
	    //   ternaryNumber.push_back( 2.0 );
    	//   ternaryNumber.push_back( 1.0 );
    	//   ternaryNumber.push_back( 0.0 );
    	// will store 2.0 1.0 0.0 in order.

      	ternaryNumber.push_back( t2 );
      	ternaryNumber.push_back( t1 );
      	ternaryNumber.push_back( t0 );

        decimalNumber = ter2dec( ternaryNumber );

        for ( int d = 0; d < numberOfDigits; d++ )
        {
          cout << ternaryNumber.at( d ) << " ";
        }
        cout << " in ternary ==> " << decimalNumber << " in decimal." << endl;

        ternaryNumber.clear();
      }
    }
  }
}
 */

void
NumberConversion::test_ter2dec()
{
  double         decimalNumber;
  int            numberOfDigits;

  numberOfDigits = 3;  // We test a case for only three digits here.

  // ternaryNumber has three bins and they are changed from 000 to 222.
  for ( double t2 = 0.0; t2 < numberOfDigits; t2+=1.0 )
  {
    for ( double t1 = 0.0; t1 < numberOfDigits; t1+=1.0 )
    {
      for ( double t0 = 0.0; t0 < numberOfDigits; t0+=1.0 )
      {
        decimalNumber = ter2dec( t2, t1, t0 );
        cout << "\t" << t2 << " " << t1 << " " << t0
             << " in ternary ==> " << decimalNumber << " in decimal."
             << endl;
      }
    }
  }
}

// ter2dec( ... )
//   Ternary to Decimal conversion
//   ternaryNumber is an array of which size is equal to numberOfDigits.
//
// The polynomial method of number conversion is used.
//   Refer to Chapter 2.4. polynomial method of number conversion (page 16) in
// Donald D. Givone, "Digital Principles and Design" or any textbook for digital
// logic.
//
// N(10): A number in decimal
// N(3):  A number in ternary
//
// r: radix or base of the number. e.g. r=3 for ternary, r=10 for decimal.
//
// N(10) = d_(n-1)*r^(n-1) +
//         d_(n-2)*r^(n-2) +
//              ...
//         d_2*r^2 +
//         d_1*r^1 +
//         d_0*r^0
//       = d_(n-1)*3^(n-1) +
//         d_(n-2)*3^(n-2) +
//              ...
//         d_2*3^2 +
//         d_1*3^1 +
//         d_0
//
// Note "_" is a subscript and "^" is a superscript.

// ter2dec( double d2, double d1, double d0 ) is a function to interface
//   ter2dec( vdouble ternaryNumber ) for the input dimension reduction technique
//   used in CSRN. The latter is the primary function that converts a vector of ternary
//   numbers to a decimal number. It takes a vector of any size and returns the converted
//   decimal number. On the other hand, the IDR converts three digits of ternary values
//   to a decimal number. It is convenient to have a function with three input arguments
//   (in ternary) and interfaces the vector for the primary function ter2dec.
//
// Push back adds a number from left to right, so d2 should be inserted to the vector first.
// In other words, ternaryNumber has d2 d1 d0. For example, the following lines will store
// 2.0 1.0 0.0 in order.
//   ternaryNumber.push_back( 2.0 );
//   ternaryNumber.push_back( 1.0 );
//   ternaryNumber.push_back( 0.0 );

double
NumberConversion::ter2dec( double d2, double d1, double d0 )
{
  vdouble ternaryNumber;
  int     decimalNumber;  // For readability

  ternaryNumber.push_back( d2 );  // If 2.0
  ternaryNumber.push_back( d1 );  // If 1.0
  ternaryNumber.push_back( d0 );  // If 0.0

  decimalNumber = ter2dec( ternaryNumber );  // then ternaryNumber is 2.0 1.0 0.0.

  return decimalNumber;
}

double
NumberConversion::ter2dec( vdouble ternaryNumber )
{
  double decimalNumber;  // This is used also as a dummy variable.
  double digit;          // The number in each digit, e.g. d_(n-1), d_(n-2), ... , d_2, d_1, d_0
  double radix;          // Radix or base of the number system, e.g. r
  int    numberOfDigits; // For readability
  int    vector_index;

  numberOfDigits = ternaryNumber.size();
  radix = 3.0;

  // Note vector_index is neccessary because ternaryNumber stores the values
  // in the reverse order of int d.
  //
  // -----------------------------------------
  //   d  vector_index        digit
  // -----------------------------------------
  //   0      2         ternaryNumber.at(2)
  //   1      1         ternaryNumber.at(1)
  //   2      0         ternaryNumber.at(0)
  //
  //   Say ternaryNumber contains "210" in ternary.
  // (Actually, it contains a double type values "2.0 1.0 0.0".)
  // Then the converted decimal number should be 21.0. In detail,
  //
  //     2.0 * 3.0^2 + 1.0 * 3.0^1 + 0.0 * 3.0^0
  //   = 2.0 * 9.0 + 1.0 * 3.0 + 0.0 * 1.0
  //   = 18.0 + 3.0
  //   = 21.0

  decimalNumber = 0;
  for ( int d = 0; d < numberOfDigits; d++ )
  {
	vector_index = (numberOfDigits - 1) - d;
	digit = ternaryNumber.at( vector_index );
	if (d ==0 )
	{
	  decimalNumber += digit;
	}
	else
	{
	  decimalNumber += digit * pow( radix, static_cast<double>(d) );
	}
  }
  return decimalNumber;
}

void
NumberConversion::test_bin2dec()
{
  int maxDigit;
  double* tmpBinary = new double [ maxDigit ];

  maxDigit = 4;

  // First convert a decimal to a binary.
  // And then convert the binary back to a decimal.
  for ( int d = 0; d < 16; d++ )
  {
    dec2bin( tmpBinary, maxDigit, d );
    cout << "   " << d << " => ";
    for ( int j = 0; j < maxDigit; j++ )
    {
      cout << tmpBinary[ j ] << " ";
    }
    cout << "=> " << bin2dec( tmpBinary, maxDigit ) << endl;
  }
  delete [] tmpBinary;
}

// int NumberConversion::bin2dec( double* binary )
//   binary to decimal, e.g. 111=>7
//   Assume binary is an array containing binary digits.
int
NumberConversion::bin2dec( double* binary, int digits )
{
  double decimal;
  int    N;

  decimal = 0.0;
  N = digits - 1;
  for ( int i = N; i >= 0  ; i-- )
  {
    decimal += pow( 2.0, (double) ( N-i ) ) * binary[ i ];
  }
  return ( ( int ) decimal );
}

// dec2bin(...)
//   Use short division by two with remainder method.
//   e.g. digits=4;
//     0 ==> 0000
//   Usage:
//     int maxDigit;
//     maxDigit = 4;
//     double* tmpBinary = new double [ maxDigit ];
//     dec2bin( tmpBinary, maxDigit, 0 );

void
NumberConversion::dec2bin( double* binary, int digits, int decimal )
{
  // d/2.0=q
  int q;  // quotient
  int r;  // remainder
  int d;  // dividend
  int i;

  for ( i = 0; i < digits; i++ )  binary[ i ] = 0.0;
  d = decimal;
  i = 0;
  while ( d > 0 )
  {
    q = static_cast< int >
        (
          static_cast< double >( d ) /
          static_cast< double >( 2 )
        );
    r = d % 2;
    d = q;
    binary[ digits - i - 1 ] = r;
    i++;
//    cout << "  " << d << "= " << q << " * 2.0 + " << r << endl;
  }
}

//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================

void
NumberConversion::showBinary( double& binary, int numOfDigits )
{
  assert( ( numOfDigits > 0 ) );
  cout << "  numOfDigits = " << numOfDigits << endl;
  cout << "  ";
  for ( int d = 0; d < numOfDigits; d++ )
  {
//    cout << *binary( d ) << " ";
  }
  cout << endl;
}

// Assume binary is already constructed.

void
NumberConversion::zeros( double* binary, int numOfDigits )
{
  assert( ( numOfDigits > 0 ) );
  for ( int d = 0; d < numOfDigits; d++ )
  {
    binary[ d ] = 0.0;
  }
}
