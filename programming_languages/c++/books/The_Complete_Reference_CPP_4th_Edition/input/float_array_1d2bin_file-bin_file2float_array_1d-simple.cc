// float_array_1d2bin_file-bin_file2float_array_1d-simple.cc

#include "pch.h"  // Comment out this in Linux. This is for Microsoft Visual Studio

// References
//   Save and read double array in a binary file : ofstream « File Stream « C++ Tutorial
//   http://www.java2s.com/Tutorial/Cpp/0240__File-Stream/Saveandreaddoublearrayinabinaryfile.htm

#include <iostream>
#include <fstream>

int main() {
  std::string file_name = "foobar.bin";
  std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
  std::cout << std::endl;

  //====================================================================================
  // Save a float type array to the output file.
  const int array_size = 10;
  float array_1d_output[array_size] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  for (int i = 0; i < array_size; i++)
    std::cout << " array_1d_output[" << i << "] = "<< array_1d_output[i] << std::endl;

  // Open a binary file
  std::ofstream ofs(file_name, std::ios::binary | std::ios::out);
  
  // Write to the binary file
  ofs.write((char*)&array_1d_output, sizeof(array_1d_output));
  std::cout << "Saved float array_1d_output to a binary file." << std::endl;

  // The following may be fine, but less efficient.
  //for (int i = 0; i < array_size; i++) {
  //  ofs.write((char*)&array_1d_output[i], sizeof(float));
  //}

  // Check the output file size
  ofs.seekp(0, std::ios::end);
  int output_file_size = ofs.tellp();
  std::cout << "output_file_size = " << output_file_size << std::endl;

  // Close ofstream.
  ofs.close();
  std::cout << std::endl;

  //====================================================================================
  // Open the binary file
  std::ifstream ifs(file_name, std::ios::binary | std::ios::in);
  if (ifs.fail()) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }

  // Read the binary file
  float array_1d_input[array_size];
  ifs.read(reinterpret_cast<char*>(&array_1d_input), sizeof(array_1d_input)); // reinterpret_cast<char*>( &variable_name )

  // Check the input file size
  ifs.seekg(0, std::ios::end);
  int input_file_size = ifs.tellg();
  std::cout << "input_file_size = " << input_file_size << std::endl;

  ifs.seekg(0, ifs.beg);  // Don't forget to bring it back to the very beginning

  // Print the float array
  for (int i = 0; i < array_size; i++)
    std::cout << " array_1d_input[" << i << "] = " << array_1d_input[i] << std::endl;
  std::cout << "Retrieved the float array from the binary file successfully." << std::endl;

  // Close ifstream.
  ifs.close();

  return 0;
}

// Expected output
//sizeof(float) = 4
//
//array_1d_output[0] = 0.1
//array_1d_output[1] = 0.2
//array_1d_output[2] = 0.3
//array_1d_output[3] = 0.4
//array_1d_output[4] = 0.5
//array_1d_output[5] = 0.6
//array_1d_output[6] = 0.7
//array_1d_output[7] = 0.8
//array_1d_output[8] = 0.9
//array_1d_output[9] = 1
//Saved float array_1d_output to a binary file.
//output_file_size = 40
//
//input_file_size = 40
//array_1d_input[0] = 0.1
//array_1d_input[1] = 0.2
//array_1d_input[2] = 0.3
//array_1d_input[3] = 0.4
//array_1d_input[4] = 0.5
//array_1d_input[5] = 0.6
//array_1d_input[6] = 0.7
//array_1d_input[7] = 0.8
//array_1d_input[8] = 0.9
//array_1d_input[9] = 1
//Retrieved the float array from the binary file successfully.
