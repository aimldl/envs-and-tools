// reinterpret_cast-int.cc

//#include "pch.h"  // Uncomment this in Visual Studio
// CPP program to demonstrate working of reinterpret_cast 
// Ref to https://www.geeksforgeeks.org/reinterpret_cast-in-c-type-casting-operators/

#include <iostream>

using namespace std;

int main() {
 int* p = new int(65);  // Initialize *p with 65
 char* ch = reinterpret_cast<char*>(p);  // 65 is A in the ASCII code

 cout << *p << endl;  // 65
 cout << *ch << endl; // A
 cout << p << endl;   // Address of int type variable p, e.g. 
 cout << ch << endl;  // A
  
 return 0;
}
