// iostream-cin_cout_simple.cc

//#include "pch.h"  // Uncomment this in Visual Studio

// Old-Style vs. Modern C++, p.267
#include <iostream>

using namespace std;

int main() {
// A Sample C++ Program, p.260
  int i;

  // Input
  cout << "This is C style output \n";
  cout << "Enter a number : ";
  cin  >> i;

  // Output
  cout << i << " is the number you entered." << endl;
  cout << endl;

// Declaring Local Variables, p.264, Example 2
  float f;
  double d;

  // Input
  cout << "Enter two floating point numbers : ";
  cin >> f >> d;

  char str[80];  // This was impossible in C89; possible in C++
  cout << "Enter a string : ";
  cin >> str;

  // Output
  cout << "This is the entered inputs : two floating numbers and a string.";
  cout << f << " " << d << endl;
  cout << str << endl;

  return 0;
}

// Old-Style vs. Modern C++, p.267
// An old-style C++ program uses <iostream.h> as folows, but it's <iostream> in this code.
//
// #include <iostream.h>
// 
// int main()
// {
//   return 0;
// }

// A Sample C++ Program, p.260
// Example 1
// This is C style output
// Enter a number : 3
// 3 is the number you entered.
//
// Example
// This is C style output
// Enter a number : 3.141592
// 3 is the number you entered.

// Declaring Local Variables, p.264, Example 2
//
// Example
// Enter two floating point numbers : 2.718281 3.141592
// Enter a string : e_and_pi
// 2.71828 3.14159
// e_and_pi

// More comments about:
// This was impossible in C89; possible in C++

// Declaring Local Variables, p.264
// This example shows an important difference between C and C++ regarding when local variables can be declared.
// In C89, you couldn’t declare a variable AFTER an action statement has occurred.
// In this example, i = 10 is the action statement.
// So the declaration of int j is impossible in C89, but possible in C++.
// The following code doesn't build, but this code does build!

// int f()
// {
//   int i;
//   i = 10;
//   int j;
//   j = i * 2;
//   return j;
// }
