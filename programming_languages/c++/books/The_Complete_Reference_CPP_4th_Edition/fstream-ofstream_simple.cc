// fstream-ofstream_simple.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <fstream>

int main() {
  // Output File Stream
  std::ofstream ofs;

  // Check this file after running this program.
  ofs.open("fstream-ofstream_simple-output.txt");
  ofs << "First line\n";
  ofs << "Second line\n";
  ofs.close();

  return 0;
}
