// strings_basics.cc

// TODO: Add more basic examples

//#include "pch.h"  // Uncomment this in Visual Studio
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	cout << "string type" << "\t" << "printf" << "\t" << "cout" << endl;
	char str1[] = "hello";
	cout << "char array" << "\t";
	printf("\'%s\'\t", str1);
	cout << "\'"<< str1 << "\'" << endl;

	char str2[6] = "hello";
	cout << "char array" << "\t";
	printf("\'%s\'\t", str2);
	cout << "\'" << str2 << "\'" << endl;

	char str3[100] = "hello";
	cout << "char array" << "\t";
	printf("\'%s\'\t", str3);
	cout << "\'" << str3 << "\'" << endl;

	char str4[100] = "hello\0";
	cout << "C-string" << "\t";
	printf("\'%s\'\t", str4);
	cout << "\'" << str4 << "\'" << endl;

	return 0;
}
