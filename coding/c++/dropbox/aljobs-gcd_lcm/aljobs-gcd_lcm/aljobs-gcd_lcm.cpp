// aljobs-gcd_lcm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

int
get_divisors(int num, int* array)
{
	int j = 0;
	for (int d = num; d > 0; d--)
	{
		if (num % d == 0)
		{
			array[j] = d;
			j++;
		}
	}
	int size = j;
	return size;
}

int
get_gcd(int** divisors, int* size)
{
	int gcd = 0;  // if 0, it's an error!

	int ref;  // reference value
	int cmp;  // Compared value
	for (int r = 0; r < size[0]; r++)
	{
		ref = divisors[0][r];
		for (int c = 0; c < size[1]; c++)
		{
			cmp = divisors[1][c];
			//			cout << r << "," << c << ": " << ref << "," << cmp << endl;
			if (ref > cmp)		break;
			else if (ref < cmp)		continue;
			else  // if (ref == cmp)
			{
				gcd = ref;
				return gcd;
			}
		}
	}
	return 0;  // There's no GCD!
}


int
get_lcm( int gcd, int num0, int num1 )
{
	int lcm = num0 * num1 / gcd;
	return lcm;
}

int main() {

	bool debug = 0;

	// Input
	int  N = 2;
	int* num = new int[N]; // num <= 10000
	// example1: 24 18
	num[0] = 24;
	num[1] = 18;

	// example2: 1000 10000
//	num[0] = 1000;
//	num[1] = 10000;

	//cin >> num[0] >> num[1];

	// Solution
	// GCD (Greatest Common Divisor)
	int gcd;  // GCD (Greatest Common Divisor)
	int size = 10000;  // because num < 10000

	// Divisors
	int** divisors = new int*[N];
	for (int j = 0; j < N; j++)
		divisors[j] = new int[size];
	int D[2];  // size of divisors arrays. Necessary to print the arrays
	for (int i = 0; i < N; i++)
	{
		D[i] = get_divisors(num[i], divisors[i]);
	}

	if (debug)
	{
		cout << "Divisors" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < D[i]; j++)
				cout << divisors[i][j] << " ";
			cout << endl;
		}
	}

	// GCD calculation
	gcd = get_gcd(divisors, D);
	if (debug)  cout << gcd << endl;

	// LCM (Least Common Multiple)
	int lcm;  // LCM (Least Common Multiple)

	lcm = get_lcm( gcd, num[0], num[1] );
	if (debug)  cout << lcm << endl;

	// Output
	if (debug) cout << "Output" << endl;
	cout << gcd << endl;
	cout << lcm << endl;

	return 0;
}

/*
int
get_lcm(int** multiples, int size)
{
	int lcm = 0;  // if 0, it's an error!

	int ref;  // reference value
	int cmp;  // Compared value
	for (int r = 0; r < size; r++)
	{
		ref = multiples[0][r];
		for (int c = 0; c < size; c++)
		{
			cmp = multiples[1][c];
			//			cout << r << "," << c << ": " << ref << "," << cmp << endl;
			if (ref < cmp)		break;
			else if (ref > cmp)		continue;
			else  // if (ref == cmp)
			{
				lcm = ref;
				return lcm;
			}
		}
	}
	return 0;  // There's no lcm!
}

int
get_multiples(int num, int* array, int size)
{
	int m;
	int val;
	int i;
	for (i = 0; i < size; i++)
	{
		m = i + 1;
		val = num * m;
		if (val <= 10000)
			array[i] = val;
		else
			return i;  // size of the array index
	}
	return i - 1;  // -1 because of i++
}
*/