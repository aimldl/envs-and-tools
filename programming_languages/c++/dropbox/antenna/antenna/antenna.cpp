// antenna.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define DEBUG 0

//int H[100002];

struct Node {
	int h;
	int idx;
} L[100002], R[100002];

int main()
{
	int N;
	int i, j;
	//scanf("%d", &N);
	//for (i = 0; i < N; i++)
	//{
	//	scanf("%d", &H[i]);

	//}
	//N = 7;
	//int H[7] = { 6, 5, 7, 3, 4, 2,10 };


	N = 8;
	int H[8] = { 6, 5, 7, 3, 4, 2,8,7 };



	L[0].h = H[0];
	L[0].idx = 0;
	R[0].h = H[N - 1];
	R[0].idx = N - 1;
	int L_count = 1;
	int R_count = 1;
	for (i = 1; i < N; i++)
	{
		if (L[i - 1].h < H[i])
		{
			L[L_count].h = H[i];
			L[L_count].idx = i;
			L_count++;
		}
	}

	for (i = N - 2; i >= 1; i--)
	{
		if (R[i + 1].h < H[i])
		{
			R[R_count].h = H[i];
			R[R_count].idx = i;
			R_count++;
		}

	}

	int maxarea = 0;
	int area;
	for (i = 0; i < L_count; i++)
	{
		for (j = 0; j < R_count; j++)
		{
			if (abs(L[i].idx - R[j].idx) >= 2)
			{
				area = min(L[i].h, R[j].h)*(abs(L[i].idx - R[j].idx) - 1);
				maxarea = max(area, maxarea);

			}
		}
	}
	printf("%d", maxarea);
}