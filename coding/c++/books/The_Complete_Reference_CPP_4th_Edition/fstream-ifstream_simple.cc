// fstream-ifstream_simple.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>
#include <fstream>

#define DEBUG 1

int main()
{
  std::ifstream ifs("fstream-ifstream_simple-input.txt");
  if (ifs.fail()) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }

  std::cout << "Hello, world!" << std::endl;
  // TODO(aimldl): Implement a loop to show the input file

  return 0;
}
