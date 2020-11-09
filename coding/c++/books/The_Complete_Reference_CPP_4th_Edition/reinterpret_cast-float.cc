// reinterpret_cast-float.cc

// TODO: Make this work

//#include "pch.h"  // Uncomment this in Visual Studio
// CPP program to demonstrate working of reinterpret_cast
// Ref. https://www.geeksforgeeks.org/reinterpret_cast-in-c-type-casting-operators/

// This code is an extension of the above example for float

#include <iostream> 
using namespace std;

int main() {
  float* pi = new float(3.141592);  // Initialize *pi with 3.141592
  char* ch  = reinterpret_cast<char*>(pi);

  cout << *pi << endl;  // 3.14159
  cout << *ch << endl;  // 
  cout << pi << endl;   // 014322F0
  cout << ch << endl;   // ? I@羲羲u省

  float e = 2.718281;  // Initialize e with 2.718281
  ch = reinterpret_cast<char*>(&e);

  cout << e << endl;   // 2.71828
  cout << *ch << endl; // Q
  cout << &e << endl;  // 010FFA40
  cout << ch << endl;  // Q ? @儆儆儆儆@?儆儆儆儆 ? C儆儆좫ZFx ? n6

  return 0;
}

//3.14159
//
//014322F0
//? I@羲羲u省
//2.71828
//Q
//010FFA40
//Q ? @儆儆儆儆@?儆儆儆儆 ? C儆儆좫ZFx ? n6
