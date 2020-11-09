// tobin_solved.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// tobin.cpp는 time limit에서 걸리므로 풀린 것이 아님. 이 것이 제대로 푼 것임!

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

// This doesn't work.
// cout << "K=" << (sizeof(pos)) / sizeof(*pos) << endl;
// So use a vector.
// k개의 size를 미리 확보해놓고, []를 써서 array처럼 쓴다.

#define DEBUG_PT1 0

void
output(int n_digits, vector<int> pos)
{
	int K = pos.size();

	int* flag = new int[n_digits];
	for (int i = 0; i < n_digits; i++)  flag[i] = 0;

	int x;
	for (int j = 0; j < K; j++)
	{
		x = pos.at(j);
		flag[x-1] = 1;
	}

	//for (int i = n_digits -1; i >=0; i--)
	for (int i = 0; i < n_digits; i++)
	{
		if (flag[i]) cout << "1";
		else         cout << "0";
	}
	cout << endl;
}

void
rf(int n_digits, int n, int k, int d, vector<int> pos)  // d: depth or digit
{
	if (DEBUG_PT1)  cout << "(" << n << "," << k << "," << d << ")"<< endl;
	// terminal condition
	if (n < k) return;  // Cut in advnace beause there's no hope!
	else
	{
		if (k == -1) return;
		else if (k == 0)
		{
			output(n_digits, pos);
			// reset pos? delete pos;
			return;
		}
	}
    // Recursion
	// 1
	if (DEBUG_PT1)  cout << "==>1\t(" << n - 1 << "," << k - 1 << "," << d + 1 << ")";
	pos[k - 1] = d + 1;
	if (DEBUG_PT1)  cout << "\tpos[" << k - 1 << "] = " << d + 1 << endl;
	rf(n_digits, n - 1, k - 1, d + 1, pos);

	// 0 
	if (DEBUG_PT1)  cout << "0<==\t(" << n-1 << "," << k << "," << d+1 << ")" << endl;
	rf(n_digits, n - 1, k, d+1, pos);
}

// Example
// n = 2; k = 1;
// n = 5; k = 2;
int main()
{
	int n;
	int k;
	cin >> n >> k;

	if (k == 0)
	{
		for (int i = 0; i < n; i++)  cout << "0";
		cout << endl;
	} else if (k == n)
	{
		for (int i = 0; i < n; i++)  cout << "1";
		cout << endl;
	} else
	{
	  vector<int> pos(k);
	  rf(n, n, k, 0, pos);
	}
}

// Wrong anwswer I got with n = 5; k = 2;
// This code has fixed this problem!
/*
11000
10100
01100
10010
01010
00110
10001
01001
00101
00011
*/