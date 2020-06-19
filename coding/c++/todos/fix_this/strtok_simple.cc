// strtok_simple.cc
// Caution: strtok is thread-unsafe. Use it with this in mind. https://jybaek.tistory.com/593

//#include "pch.h"  // Uncomment this in Visual Studio
#include <cstdio>
#include <cstring>

int main()
{
  char str[] = "This,is,a,sample,string,";
  char* ptr; // pointer

  printf("Before: '%s''\n", str);

  ptr = strtok(str, ",");
  while (ptr != NULL) {
    printf("%s\n", ptr);
    ptr = strtok(NULL, ",");
  }
  printf("After: '%s''\n", str);
}

// “Split” is a basic operation for string manipulation.
// Original string: “This,is,a,sample,string,”
// Delimiter: “,”
// Tokens:
// This
// is
// a
// sample
// string
//
// In C++, this split operation can be nicely done with strtok.
// strtok is a C’s built-in function for string tokenization.
// In this example, a string “This,is,a,sample,string,” is split into five tokens delimited by “,”. In other words,
