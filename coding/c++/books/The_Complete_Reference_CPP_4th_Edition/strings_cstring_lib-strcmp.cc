// strings_cstring_lib-strcmp.cc

//#include "pch.h"                 // Uncomment this in Visual Studio
//#define _CRT_SECURE_NO_WARNINGS  // Uncomment this in Visual Studio

#include <cstdio>
#include <cstring>

int main() {
	printf("Enter two strings in two lines\n");

	// Take the input from 
	char str1[100], str2[100];
	scanf("%s", str1);
	scanf("%s", str2);

	if (strcmp(str1, str2) == 0) {
		printf("Same!\n");
	}
	else {
		printf("Different!\n");
	}

	return 0;
}
