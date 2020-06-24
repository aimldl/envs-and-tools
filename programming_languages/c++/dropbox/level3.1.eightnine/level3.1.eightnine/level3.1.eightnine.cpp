// level3.1.eightnine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.


#include "pch.h"
#include <iostream>
using namespace std;

int main() {

	// Input
	int N;
	int M;
	cin >> N >> M;

	int** arr = new int*[N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];
	/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	*/

	// Flip the matrix & Output
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr[i][M-1-j] << " ";
		}
		cout << endl;
	}

	return 0;
}