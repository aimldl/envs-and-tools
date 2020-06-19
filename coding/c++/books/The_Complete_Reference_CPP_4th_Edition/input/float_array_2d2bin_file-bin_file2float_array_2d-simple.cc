// float_array_2d2bin_file-bin_file2float_array_2d-simple.cc

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
  const int row_size = 5;
  const int col_size = 4;

  // Declare a two-dimensional array
  float** array_2d_output = new float*[row_size];
  for (int r = 0; r < row_size; r++)
    array_2d_output[r] = new float[col_size];

  // Initialize array_2d_output
  float num = 0.0;
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      array_2d_output[r][c] = num;
      num += 0.1;
    }
  }

  // Show the values in array_2d_output
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      std::cout << array_2d_output[r][c] << " ";
    }
    std::cout << std::endl;
  }

  // Open a binary file
  std::ofstream ofs(file_name, std::ios::binary | std::ios::out);

  // Write to the binary file
  ofs.write((char*)&array_2d_output, sizeof(array_2d_output));
  std::cout << "Saved float array_2d_output to a binary file." << std::endl;

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

  // Declare a two-dimensional array
  float** array_2d_input = new float*[row_size];
  for (int r = 0; r < row_size; r++)
    array_2d_input[r] = new float[col_size];

  // Read the binary file
  ifs.read(reinterpret_cast<char*>(&array_2d_input), sizeof(array_2d_input)); // reinterpret_cast<char*>( &variable_name )

  // Check the input file size
  ifs.seekg(0, std::ios::end);
  int input_file_size = ifs.tellg();
  std::cout << "input_file_size = " << input_file_size << std::endl;

  ifs.seekg(0, ifs.beg);  // Don't forget to bring it back to the very beginning

  // Show the values in array_2d_input
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      std::cout << array_2d_input[r][c] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Retrieved the float array from the binary file successfully." << std::endl;  

  // Close ifstream.
  ifs.close();

  return 0;
}

// Expected output
//sizeof(float) = 4
//
//0 0.1 0.2 0.3
//0.4 0.5 0.6 0.7
//0.8 0.9 1 1.1
//1.2 1.3 1.4 1.5
//1.6 1.7 1.8 1.9
//Saved float array_2d_output to a binary file.
//output_file_size = 4
//
//input_file_size = 4
//0 0.1 0.2 0.3
//0.4 0.5 0.6 0.7
//0.8 0.9 1 1.1
//1.2 1.3 1.4 1.5
//1.6 1.7 1.8 1.9
//Retrieved the float array from the binary file successfully.
