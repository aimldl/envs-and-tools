
#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>
#include <set>

using namespace std;

int main() {

	auto x = 2;
	auto y = 3.141592;
	auto z = &x;

	// Show the typeid of each variable
	cout << typeid(x).name() << endl;  // int 
	cout << typeid(y).name() << endl;  // double
	cout << typeid(z).name() << endl;  // int *

	return 0;
}