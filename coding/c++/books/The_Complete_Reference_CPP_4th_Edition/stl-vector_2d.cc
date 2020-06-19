// stl-vector_2d.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>
#include <vector>

int main()
{
  std::vector< std::vector<int> > vect_2d{ {1,2,3}, {4,5,6}, {7,8,9} };

  // Option 1
  int row_size = vect_2d.size();
  int col_size;
  for (int r = 0; r < row_size; r++) {
    col_size = vect_2d[r].size();
    for (int c = 0; c < col_size; c++) {
      std::cout << vect_2d[r][c] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // Option 2
  for (int r = 0; r < vect_2d.size(); r++) {
    for (int c = 0; c < vect_2d[r].size(); c++) {
      std::cout << vect_2d[r][c] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
