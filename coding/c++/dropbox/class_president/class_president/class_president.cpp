// class_president.cpp

#include "pch.h"
#include <iostream>
#include <fstream>

#define DEBUG 1
//#define DEBUG 0

void
show1darray(int* arr, int N);

void
show2darray(int** arr, int N, int Y);

//any_match(int** row1, int** row2, int column_size)
bool
any_match(int* row1, int* row2, int column_size)
{
	for (int j = 0; j < column_size; j++)
	{
		if (row1[j] == row2[j])
		{
			return true;
		}
	}
	return false;
}

int
find_max(int* arr, int N)
{
	int idx_max = 0;
	int max_val = arr[0];

	for (int i = 1; i < N; i++)
	{
		if (max_val < arr[i])
		{
			idx_max = i;
			max_val = arr[i];
		}
	}
	return idx_max;
}

int
main()
{
	std::ifstream ifs("class_president_ex-1.txt");

	// Input
	int N;
	ifs >> N;

	int Y = 5;  // class years
	int ** tbl = new int *[N];
	for (int i = 0; i < N; i++)
		tbl[i] = new int[Y];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			ifs >> tbl[i][j];
		}
	}
	if (DEBUG) show2darray(tbl, N, Y);

	// Find the temporary class president
	int* hist_c_ptr;  // pointer to the history of candidate
	int* hist_s_ptr;  // pointer to the history of students
	int* num_classmates = new int[N];

	for (int c = 0; c < N; c++)  // c = candidate for the class president
	{
		hist_c_ptr = tbl[c];
		num_classmates[c] = 0;

		// Compare with other students
		for (int s = 0; s < N; s++)
		{
			if ( c != s )
			{
				hist_s_ptr = tbl[s];
				if ( any_match( hist_c_ptr, hist_s_ptr, Y ) )
				{
					num_classmates[c]++;
				}
			}
		}
	}
	if (DEBUG) show1darray(num_classmates, N);

	// Find the candidate with the max number of classmates
	int idx_president;
	idx_president = find_max(num_classmates, N);

	// Output
	std::cout << idx_president+1 << std::endl;  // Note add 1

	return 0;
}

void
show1darray(int* arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void
show2darray(int** arr, int N, int Y)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
	// Find the temporary class president

	int** hist_c_ptr;  // pointer to the history of candidate
	int** hist_s_ptr;  // pointer to the history of students
	int* num_classmates = new int[N];

	for (int c = 0; c < N; c++)  // c = candidate for the class president
	{
		hist_c_ptr = &tbl[c];
		num_classmates[c] = 0;

		// Compare with other students
		for (int s = 0; s < N; s++)
		{
			if ( c != s )
			{
				hist_s_ptr = &tbl[s];
				if ( any_match(hist_c_ptr, hist_s_ptr, Y) )
				{
					num_classmates[c]++;
				}
			}
		}
	}
*/