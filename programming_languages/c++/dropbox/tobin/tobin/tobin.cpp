// tobin.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <cstdio>
//#include <iostream>
using namespace std;

void
rf(int N, int k, int i, int c, bool* arr)  // c is for count
{
	if (i == -1)  // terminal condition
	{
		if (c == k)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				printf("%d", arr[j]);
				//cout << arr[j];
			}
			printf("\n");
			//cout << endl;
		}
		return;
	}
	arr[i] = 1;
	rf(N, k, i - 1, ++c, arr);
	c--;
	arr[i] = 0;
	rf(N, k, i - 1, c, arr);
}

int main() {

	// Input
	int n, k;
	//cin >> n >> k;
	//scanf("%d %d", &n, &k);
	n = 5;
	k = 3;

	// Output
	bool* arr = new bool[n];
	rf(n, k, n - 1, 0, arr);

	return 0;
}

// For n=2,k=1
// 10
// 01
/*
int i = n - 1;
arr[i] = 0;
rf(N, n - 1, k, c, arr);

arr[i] = 1;
rf(N, n - 1, k, ++c, arr);
*/

// For n=2,k=1
// 01
// 10
/*
int i = n - 1;
arr[i] = 1;
rf(N, n - 1, k, ++c, arr);
c--;
arr[i] = 0;
rf(N, n - 1, k, c, arr);
*/

/*
This part works properly except the last two problems.
Time Exceeds.
void
rf(int N, int k, int i, int c, int* arr)  // c is for count
{
	if (i == -1)  // terminal condition
	{
		if (c == k)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				printf("%d", arr[j]);
				//cout << arr[j];
			}
			printf("\n");
			//cout << endl;
		}
		return;
	}
	arr[i] = 1;
	rf(N, k, i - 1, ++c, arr);
	c--;
	arr[i] = 0;
	rf(N, k, i - 1, c, arr);
}

int main() {

	// Input
	int n, k;
	//cin >> n >> k;
	//scanf("%d %d", &n, &k);
	n = 5;
	k = 3;

	// Output
	int* arr = new int[n];
	rf(n, k, n - 1, 0, arr);

	return 0;
}

*/

/*
This part doens't work properly after changing everything to unsigned short
void
rf(unsigned short int N, unsigned short int k, short int i, short int c, int* arr)  // c is for count
{
	if (i == -1)  // terminal condition
	{
		if (c == k)
		{
			for (unsigned short int j = N-1; j >= 0; j--)
			{
				printf("%d",arr[i]);
				//cout << arr[j];
			}
			printf("\n");
			//cout << endl;
		}
		return;
	}
	arr[i] = 1;
	rf(N, k, i-1, ++c, arr);
	c--;
	arr[i] = 0;
	rf(N, k, i-1, c, arr);
}

int main() {

	// Input
	unsigned short int n, k;
	//cin >> n >> k;
	scanf("%hu %hu",&n,&k);
	//n = 5;
	//k = 3;

	// Output
	int* arr = new int[n];
	rf(n, k, n-1, 0, arr);

	return 0;
}

*/