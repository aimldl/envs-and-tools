// color_paper.cpp

#include "pch.h"
#include <iostream>
#include <fstream>

#define DEBUG 1
//#define DEBUG 0

void
showbrd(int** brd2d)
{
	int S;
	if (DEBUG)  S = 20;
	else        S = 101;
	
	for (int r = 0; r < S; r++)
	{
		for (int c = 0; c < S; c++)
		{
			std::cout << brd2d[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	// Input
	int N;
	std::ifstream ifs("color_paper-ex1.txt");
	ifs >> N;

	int** p_cfg = new int* [N];  // paper configuration
	for (int i = 0; i < N; i++)
		p_cfg[i] = new int[4];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 4; j++)
			ifs >> p_cfg[i][j];
	}

	// For each color paper, create a board.
	int S;
	if (DEBUG)  S = 20;
	else        S = 101;

	int*** brd = new int**[N];
	for (int p = 0; p < N; p++)
	{
		brd[p] = new int*[S];
		for (int r = 0; r < S; r++)
		{
			brd[p][r] = new int[S];
		}
	}

	// Initialize 
	for (int p = 0; p < N; p++)
	{
		for (int r = 0; r < S; r++)
		{
			for (int c = 0; c < S; c++)
			{
				brd[p][r][c] = 0;
			}
		}

	}

	// Mark each board with color papers
	int x, y;
	int w, h;  // witdth, height
	for (int p = 0; p < N; p++)
	{
		x = p_cfg[p][0];
		y = p_cfg[p][1];
		w = p_cfg[p][2];
		h = p_cfg[p][3];

		if (DEBUG) std::cout << x << " " << y << " " << w << " " << h << std::endl;
		for (int r = x; r < x+w; r++)
		{
			for (int c = y; c < y+h; c++)
			{
				brd[p][r][c] = 1;
			}
		}
		if (DEBUG) showbrd(brd[p]);
		if (DEBUG) getchar();

		for (int i = p - 1; i >= 0; i--)
		{
			// Substract
			for (int r = x; r < x + w; r++)
			{
				for (int c = y; c < y + h; c++)
				{
					brd[i][r][c] = 0;  // Note it's brd[i][...], not brd[p][...]
				}
			}
			if (DEBUG) showbrd(brd[i]);
			if (DEBUG) getchar();
		}
	}

	// Get the sum or the area by each color paper
	int* sum = new int[N];
	for (int i = 0; i < N; i++) sum[i] = 0;

	for (int p = 0; p < N; p++)
	{
		x = p_cfg[p][0];
		y = p_cfg[p][1];
		w = p_cfg[p][2];
		h = p_cfg[p][3];

		if (DEBUG) std::cout << x << " " << y << " " << w << " " << h << std::endl;
		if (DEBUG) showbrd(brd[p]);
		for (int r = x; r < x + w; r++)
		{
			for (int c = y; c < y + h; c++)
			{
				sum[p] += brd[p][r][c];
			}
		}
		if (DEBUG) std::cout << p << ": " << sum[p] << std::endl;
		else       std::cout << sum[p] << std::endl;
		if (DEBUG) getchar();
	}
	return 0;
}