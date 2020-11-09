// sorting_algo-bubble_sort.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>
#include <fstream>

#define DEBUG 1

void ShowArray1D(int *array, int &size)
{
  for (int i = 0; i < size; i++)
    std::cout << array[i] << " ";
  std::cout << std::endl;
}

void Swap(int &var1, int &var2)
{
  int temp;
  temp = var1;
  var1 = var2;
  var2 = temp;
}

void BubleSort(int *array, int &size)
{
  if (DEBUG) std::cout << "bar: values in the array" << std::endl;
  for (int bar = size - 1; bar >= 0; bar--)
  {
    if (DEBUG) std::cout << bar << ": ";
    if (DEBUG) ShowArray1D(array, size);
    
    // Caution: i < bar, not i< size-1
    for (int i = 0; i < bar; i++) {
      if (array[i] > array[i + 1]) {
        Swap(array[i], array[i + 1]);
      }
    }
  }
}

int main()
{
  std::ifstream ifs("sorting_algo-bubble_sort-input.txt");
  if (ifs.fail()) {
    std::cerr << "File not found" << std::endl;
    return 1;
  }

  // Input
  int element_size;
  ifs >> element_size;
  
  int* array_1d = new int[element_size];
  for (int i = 0; i < element_size; i++)
    ifs >> array_1d[i];
  
  if (DEBUG) std::cout << "The input or unsorted array" << std::endl;
  if (DEBUG) ShowArray1D(array_1d, element_size);
  if (DEBUG) std::cout << std::endl;
  
  // Sorting
  BubleSort(array_1d, element_size);

  // Output
  if (DEBUG) std::cout << std::endl;
  if (DEBUG) std::cout << "The output or sorted array " << std::endl;
  ShowArray1D(array_1d, element_size);

  return 0;
}
