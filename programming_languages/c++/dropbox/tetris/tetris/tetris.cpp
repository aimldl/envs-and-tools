// tetris.cpp

#include "pch.h"
#include <iostream>
#include <fstream>

// tetris-ex1.txt
// Expected output
// 4 3

#define DEBUG 0

void
show2darray(int** arr, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// If any column of the row is zero or 0, this row is not filed with 1
bool
is_filled_wt_one(int* row_ptr, int size_column)
{
	for (int i = 0; i < size_column; i++)
	{
		if (row_ptr[i] == 0)
		{
			return false;
		}
	}
	return true;
}

int
num_deleted_bars(int** map, int R, int C)
{
	// Count the bars from the bottom
	int* row_ptr;
	int count = 0;
	for (int y = R - 1; y >= 0; y--)  // Watch "int y = R" fails
	{
		row_ptr = map[y];
		if (is_filled_wt_one(row_ptr, C))
			count++;
		else
			break;
	}
	return count;
}

int*
find_max(int* arr, int N)
{
	int idx_max = 0;
	int max_val = arr[0];
	int* answer = new int[2];

	for (int i = 1; i < N; i++)
	{
		if (max_val < arr[i])
		{
			idx_max = i;
			max_val = arr[i];
		}
	}
	answer[0] = idx_max;
	answer[1] = max_val;
	return answer;
}

int
main()
{
	// Input
	std::ifstream ifs("tetris-ex1.txt");
	int C;  // Column, 5 <= C, R <=20
	int R;  // Row
	ifs >> C >> R;

	int** map = new int*[R];
	for (int r = 0; r < R; r++)
		map[r] = new int[C];

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			ifs >> map[r][c];
		}
	}
	if (DEBUG) show2darray(map, R, C);

	// Find X & Y
	int X;  // Location from the left 
	int Y;  // Height of erased bars
	int* nums = new int[C];

	int** map2 = new int*[R];
	for (int r = 0; r < R; r++)
		map2[r] = new int[C];

	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
			map2[r][c] = map[r][c];

	if (DEBUG) show2darray(map2, R, C);
	int tetris;
	for (int x = 0; x < C; x++)
	{
		tetris = 0;
		for (int y = R-1; y >=0; y--)
		{
			if (DEBUG)  std::cout << map2[y][x] << " " << x << "," << y << "\n";
			if (map2[y][x]) continue;
			else
			{
				if (tetris < 4)
				{
					map2[y][x] = 1;
					tetris++;
				}
			}
		}
		if (DEBUG) show2darray(map2, R, C);
		nums[x] = num_deleted_bars(map2, R, C);

		for (int y = R - 1; y >= 0; y--)
		{
			map2[y][x] = map[y][x];
		}
		if (DEBUG) show2darray(map2, R, C);
	}

	// Output
	int* answer = new int[2];
	answer = find_max(nums, C);
	std::cout << answer[0]+1 << " " << answer[1] << std::endl;

	return 0;
}