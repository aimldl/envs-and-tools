// float2bin_file-bin_file2float-simple.cc

#include "pch.h"  // Uncomment this in Visual Studio

// References
//   Input/output with files - C++ Tutorials, http://www.cplusplus.com/doc/tutorial/files/
//   How to write binary file in C++, https://codeyarns.com/2013/12/27/how-to-write-binary-file-in-c/
//   How to find size of file in C++, https://codeyarns.com/2018/02/02/how-to-find-size-of-file-in-c/
//   Conversion from binary data to float - C++ Forum, http://www.cplusplus.com/forum/beginner/153202/

#include <iostream>
#include <fstream>

int main() {
  std::string file_name = "foobar.bin";
  std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
  std::cout << std::endl;

  // Save a floating value of 3.141592 to the output file.
  float f_output = 3.141592;
  std::cout << "f_output = " << f_output << std::endl;

  // Open a binary file and save the floating value to it.
  std::ofstream ofs(file_name, std::ios::binary | std::ios::out);
  ofs.write( (char*)&f_output, sizeof(float) );
  std::cout << "Saved " << f_output << " to a binary file." << std::endl;

  // Let's check the output file size
  ofs.seekp(0, std::ios::end);
  int output_file_size = ofs.tellp();
  std::cout << "output_file_size = " << output_file_size << std::endl;

  // Close ofstream.
  ofs.close();
  std::cout << std::endl;

  // Open the binary file
  std::ifstream ifs(file_name, std::ios::binary | std::ios::in);
  if (ifs.fail()) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }

  // Check the input file size
  ifs.seekg(0, std::ios::end);
  int input_file_size = ifs.tellg();
  std::cout << "input_file_size = " << input_file_size << std::endl;

  // Don't forget to read the value from the very beginning
  ifs.seekg(0, ifs.beg);
  float f_input;
  ifs.read( reinterpret_cast<char*>(&f_input), sizeof(float) ); // reinterpret_cast<char*>( &variable_name )

  std::cout << "f_input = " << f_input << std::endl;
  std::cout << "Retrieved " << f_input << " from the binary file successfully." << std::endl;

  // Close ifstream.
  ifs.close();

  return 0;
}

// Expected output
//sizeof(float) = 4
//
//f_output = 3.14159
//Saved 3.14159 to a binary file.
//output_file_size = 4
//
//input_file_size = 4
//f_input = 3.14159
//Retrieved 3.14159 from the binary file successfully.
