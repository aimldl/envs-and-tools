// bin2dec.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

int
dec2bin(int divident)
{
	// returning 0 is a dummy number to avoid an error message not returning integer.
	if (divident == 0) return 0;

	int remainder = divident % 2;
	divident /= 2;      // or divident = divident >> 1;
	dec2bin(divident);
	cout << remainder;
	return 0;
}

int main()
{
	int dec;
//	dec = 14;  //1110
//	dec = 31;  // 11111
	cin >> dec;
	dec2bin(dec);
	return 0;
}