// bingo.cpp

#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;
#define DEBUG0 0
#define DEBUG1 0
#define DEBUG2 1

void
show2darray(int** arr, int R, int C)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void
swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

void
bubble_sort(int* arr,int N)
{
	int b = N;  // bar
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < b-1; j++)  // j < b-1
		{
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
		b--;
	}
}

void
check_num(int** S, int** F, int num, int R, int C)
{
	if (DEBUG2) show2darray(S, R, C);
	if (DEBUG2) cout << endl;

	int curr;  // current number
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			curr = S[i][j];  // For easier debugging
			if ( curr == num)
			{
				F[i][j] = 1;
			}
		}
	}

	if (DEBUG2) show2darray(F, R, C);
	if (DEBUG2) cout << endl;
}

bool
is_bingo(int** F, int R, int C);

int
main()
{
    // Input
	int N = 5;
	int** B = new int*[N];  // board
	for (int i = 0; i < N; i++)
		B[i] = new int[N];
	//ifstream ifs("bingo-test.txt");
	ifstream ifs("bingo-ex1.txt");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ifs >> B[i][j];
		}
	}
	if (DEBUG0) show2darray(B, N, N);
	if (DEBUG0) cout << endl;

	int** seq  = new int*[N];  // Sequence of input numbers
	for (int i = 0; i < N; i++)
		seq[i] = new int[N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ifs >> seq[i][j];
		}
	}
	if (DEBUG0) show2darray(seq, N, N);
	if (DEBUG0) cout << endl;

    // State & Flag
	int   R = 12;
	int** S = new int*[R];  // State
	int** F = new int*[R];  // Flag
	for (int i = 0; i < R; i++)
	{
		S[i] = new int[N];
		F[i] = new int[N];
	}

	// Reformat the bingo board
	int r;
	int c;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < N; j++)
		{
			    if (i >= 0 && i <= 4)
			{
				r = i;
				c = j;
			}
			else if ( i>=5 && i<=9 )
			{
				r = j;
				c = i-N;
			}
			else if (i == 10)
			{
				r = j;
				c = j;
			}
			else if (i == 11)
			{
				r = j;
				c = N-1-j;
			}
				S[i][j] = B[r][c];
				F[i][j] = 0;    // Initialize the flag
		}
	}
	if (DEBUG0) show2darray(S,R,N);
	if (DEBUG0) cout << endl;
	if (DEBUG0) show2darray(F, R, N);
	if (DEBUG0) cout << endl;

	// Now consider the sequence of the input numbers

	int num;  // number
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			count++;
			num = seq[i][j];
			if (DEBUG2) cout << num << endl;
			check_num(S,F,num,R,N);

			if (is_bingo(F, R, N))
			{
				cout << count << endl;
				return 0;
			}
//			if (DEBUG2) getchar();
			/*
			if (count >= 12)
			{
				if (is_bingo(F,R,N))
				{
					cout << num << endl;
					return 0;
				}
			}
			*/
		}
	}

	return 0;
}

// I may implement this function more elegantly.
// But I won't be bothered to do so.
// The board size is 5x5, so I don't have to make it efficient.
bool
is_bingo(int** F, int R, int C)
{
	int sum;
	int num_line = 0;  // Number of lines
	for (int i = 0; i < R; i++)
	{
		sum = 0;
		for (int j = 0; j < C; j++)
		{
			sum += F[i][j];
		}
		// If all the elements in the row is checked, it'll be 5.
		if (sum == C)      num_line++;
		if (num_line >= 3)
		{
			return true;
		}
	}
	return false;
}