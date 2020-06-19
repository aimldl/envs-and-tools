// mine.cpp

#include "pch.h"
#include <iostream>
#include <fstream>

// #define DEBUG 1
#define DEBUG 0

void
show2darray( int** arr, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int
main()
{
	// Input
	std::ifstream ifs("mine-test.txt");
	int N, M;
	int X, Y;

	ifs >> N >> M;
	ifs >> X >> Y;

	int** map = new int*[N];
	for (int i = 0; i < N; i++)
		map[i] = new int[M];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			ifs >> map[i][j];
		}
	}

	if (DEBUG)  show2darray(map, N, M);
	if (DEBUG)  std::cout << std::endl;

	// Solution: use a pad or zero-padded map
	int N_pad = N + 2;
	int M_pad = M + 2;
	int** pad = new int*[N_pad];
	for (int i = 0; i < N_pad; i++)
		pad[i] = new int[M_pad];

	// Zero-padding
	for (int j = 0; j < M_pad; j++)
	{
		pad[0][j] = 0;
		pad[N_pad-1][j] = 0;
	}
		
	for (int i = 0; i < N_pad; i++)
	{
		pad[i][0] = 0;
		pad[i][M_pad - 1] = 0;
	}

	// Copy map to the center of pad
	int i, j;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			i = n + 1;
			j = m + 1;
			pad[i][j] = map[n][m];
		}
	}

	if (DEBUG)  show2darray(pad, N_pad, M_pad);
	if (DEBUG)  std::cout << std::endl;

	// Count the mine

	if (pad[X][Y] == 1)
	{
		std::cout << "game over" << std::endl;
	}
	else
	{
		int sum = 0;
		for (i = X - 1; i <= X + 1; i++)
		{
			for (j = Y - 1; j <= Y + 1; j++)
			{
				sum += pad[i][j];
			}
		}
		std::cout << sum << std::endl;
	}
	return 0;
}