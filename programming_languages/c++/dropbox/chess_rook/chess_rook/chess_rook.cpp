// chess_rook.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <fstream>

#include <iostream>

using namespace std;

// Song: Don't stop believe in...

// Input example
//0 3 0 0 0 0 0 0
//3 1 0 0 0 0 2 0
//0 3 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0

#define DEBUG 0

void
cout_B(int N, int** B)
{
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			cout << B[x][y] << " ";
		}
		cout << endl;
	}
}

bool
is_king_caught(int N, int** B)
{
	int K[2];     // King, ( K[0], K[1] )=(x,y)
	int R[2][2];  // There're two rooks.

	// First, find King's location 
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (B[x][y] == 1)
			{
				K[0] = x;
				K[1] = y;
				break;  // No need to loop through because there's only one king.
			}
		}
	}

	// Check the cross at King's location (xx, yy)
	int xx = K[0];
	int yy = K[1];

	if (DEBUG)  cout << "King is at (" << xx << "," << yy << ")" << endl;

	enum direction {none, top, bottom, left, right};
	direction rook_location[2] = {none, none};

	int i = 0;  // Rook's index. Either 0 or 1

	// Check the column at (?, yy) where yy is fixed.
	for (int r = 0; r < N; r++)
	{
		if (B[r][yy] == 2)
		{
			R[i][0] = r;
			R[i][1] = yy;
			if (r < xx)
			{
				rook_location[i] = top;
			} else
			{
				rook_location[i] = bottom;
			}
			i++;
		}
	}

	// Check the row at (xx, ?) where xx is fixed.
	for (int c = 0; c < N; c++)
	{
		if (B[xx][c] == 2)
		{
			R[i][0] = xx;
			R[i][1] = c;
			if (c < yy)
			{
				rook_location[i] = left;
			} else
			{
				rook_location[i] = right;
			}
			i++;
		}
	}

	if (DEBUG)
	{
		for (int j = 0; j < i; j++)
		{
			cout << "Rook is at (" << R[j][0] << "," << R[j][1] << ") ";
			cout << "on the ";
			     if (rook_location[j] == top)    cout << "top";
			else if (rook_location[j] == bottom) cout << "bottom";
			else if (rook_location[j] == left)   cout << "left";
			else if (rook_location[j] == right)  cout << "right";
			cout << " of king." << endl;
		}
	}
	// Check
	if (i == 0) return false;  // Not caught because no rook is within the cross.
	else if (i == 1)
	{
		if (rook_location[0] == top)
		{
			for (int r = R[0][0] + 1; r <= K[0] - 1; r++)
			{
				if (B[r][yy] == 3) return false;
			}
		}
		else if (rook_location[0] == bottom)
		{
			for (int r = K[0] + 1; r <= R[0][0] - 1; r++)
			{
				if (B[r][yy] == 3) return false;
			}
		}
		else if (rook_location[0] == left)
		{
			for (int c = R[0][1] + 1; c <= K[1] - 1; c++)
			{
				if (B[xx][c] == 3) return false;
			}
		}
		else if (rook_location[0] == right)
		{
			for (int c = K[1] + 1; c <= R[0][1] - 1; c++)
			{
				if (B[xx][c] == 3) return false;
			}
		}
	}
	else if (i == 2)
	{
		for (int n = 0; n < 2; n++)
		{
			if (rook_location[0] == top)
			{
				for (int r = R[n][0] + 1; r <= K[0] - 1; r++)
				{
					if (B[r][yy] == 3) return false;
				}
			}
			else if (rook_location[0] == bottom)
			{
				for (int r = K[0] + 1; r <= R[n][0] - 1; r++)
				{
					if (B[r][yy] == 3) return false;
				}
			}
			else if (rook_location[0] == left)
			{
				for (int c = R[n][1] + 1; c <= K[1] - 1; c++)
				{
					if (B[xx][c] == 3) return false;
				}
			}
			else if (rook_location[0] == right)
			{
				for (int c = K[1] + 1; c <= R[n][1] - 1; c++)
				{
					if (B[xx][c] == 3) return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	ifstream ifs("chess_brd-02.txt");

	// Input
	int N = 8;
	int **B = new int* [N];  // board
	for (int x = 0; x < N; x++)
		B[x] = new int[N];

	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			ifs >> B[x][y];
			//cin >> B[x][y];
		}
	}
	if (DEBUG)  cout_B(N, B);

	// Output
	if (is_king_caught(N, B))  cout << "1" << endl;
	else                       cout << "0" << endl;

	return 0;
}