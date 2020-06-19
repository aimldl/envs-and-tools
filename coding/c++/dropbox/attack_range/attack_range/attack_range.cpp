// attack_range.cpp
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int
get_range(int x1, int y1, int X, int Y, int R)
{
	int range = abs(x1-X) + abs(y1-Y);
	     if (range == 0) return 120;  // 'x' in ASCII Code
	else if (range <= R) return range;
	else                 return 0;  // range >4
}

int main() {

	// Input
	int N;     // Map size is NxN
	int X, Y;  // Location of the unit. (X,Y) where X is row, Y is column
	int R;     // Max range

	std::ifstream ifs("attack_range-ex2.txt");
	ifs >> N;
	ifs >> X >> Y >> R;
/*
	int** map = new int*[R];
	for (int i = 0; i < R; i++)
		map[i] = new int[R];
*/

	// get_range & output
	int r;
	for (int x = 1; x <= N; x++)
	{
		for (int y = 1; y <= N; y++)
		{
			r = get_range(x, y, X, Y, R);
			if ( r==120 )  std::cout << 'x' << " ";
			else    	   std::cout << r << " ";

		}
		std::cout << std::endl;
	}

	return 0;
}