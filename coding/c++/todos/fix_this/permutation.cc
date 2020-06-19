// permutation.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <cstdlib>
#include <iostream>

void Backtrace (int d_, int* S_);
void printS (int n_, int* S_);

int main()
{
  int n = 4;
  int* S = new int [n];
  for (int i = 0; i < n; i++) {
    S[i] = i;
  }
  printS(n,S);

  for (int depth = 0; depth < n; depth++) {
    Backtrace(depth,S);
  }

  return 0;
}

void Backtrace(int d, int* S_)
{
}

void printS (int n_, int* S_)
{
  for (int i = 0; i < n_; i++) {
    std::cout << S_[i] << " ";
  }
  std::cout << std::endl;
}
