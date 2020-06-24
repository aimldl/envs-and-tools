// factorial.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

int
factorial(int num)
{
	if (num == 1 || num == 0)
		return 1;
	return num * factorial(num - 1);
}

/*
The following code snippet works as well, but the above code is way shorter than this!
int
factorial(int num)
{
	if (num > 1)
	{
		return num * factorial(num - 1);
	}
	else if ( num>=0 )
	{
		return 1;
	}
}*/

int main()
{
	int N = 10;
	for ( int n=1; n<=N; n++ )
	  cout << "factorial(" << n << ")=" << factorial(n) << endl;
	return 0;
}