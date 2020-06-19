// array_2d.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>
#include <fstream>

#define DEBUG 1

void ShowArray2D(int** array, int row_size, int col_size) {
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      std::cout << array[r][c] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  // Read the input file
  std::ifstream ifs("array_2d-input.txt");
  if (ifs.fail()) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }

  int row_size;
  int col_size;
  ifs >> row_size >> col_size;

  // Declare a two-dimensional array
  int** array_2d = new int*[row_size];
  for (int r = 0; r < row_size; r++)
    array_2d[r] = new int[col_size];

  // Get the elements of the matrix
  for (int r = 0; r < row_size; r++) {
    for (int c = 0; c < col_size; c++) {
      ifs >> array_2d[r][c];
    }
  }

  // Print of cout the matrix to verify that the matrix is read properly.
  if (DEBUG) ShowArray2D(array_2d, row_size, col_size);

  return 0;
}
