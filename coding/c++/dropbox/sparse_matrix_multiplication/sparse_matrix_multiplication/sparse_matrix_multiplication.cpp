// sparse_matrix_multiplication.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#define DEBUG  0
#define DEBUG2 1
#define DEBUG3 0

// Example Input: string s = "3 4 1 2 1 0 0 2 0 1 4 0 0 0";
vector<short int>
str2short(string s )
{
	stringstream ss;
	string out;
	short int num;
	vector<short int> seq;

	ss << s;
	while (ss >> out)
	{
		stringstream convert(out);
		convert >> num;
        seq.push_back(num);
		if (DEBUG) printf("%d\n", num);
	}
	return seq;
}

void
cout_1d_vect(vector<short int> arr)
{
	cout << "arr.size()=" << arr.size() << endl;
	for (short int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void
cout_2d_vect(vector<vector<short int>> arr)
{
	cout << "(" << arr.size() << "x" << arr[0].size() << ") matrix" << endl;
	for (short int i = 0; i < arr.size(); i++)
	{
		for (short int j = 0; j < arr[i].size(); j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void
convert2d(vector<short int> vect_1d, vector<vector<short int>>* mat_2d, short int R, short int C)
{
	short int i = 0;
	for (short int r = 0; r < R; r++)
	{
		for (short int c = 0; c < C; c++)
		{
			i = C * r + c;
			mat_2d->at(r).at(c) = vect_1d[i];
		}
	}
}

void
multiply_sparse_matrix(vector<short int> vectA, vector<short int> vectB)
{
	// Assign two leading numbers to row & col
	short int rowA = vectA.at(0);
	short int colA = vectA.at(1);
	short int rowB = vectB.at(0);
	short int colB = vectB.at(1);
	if (DEBUG) cout << "A: " << rowA << "x" << colA << endl;
	if (DEBUG) cout << "B: " << rowB << "x" << colB << endl;

	// Remove the first two elements from vectA & vectB
	if (DEBUG) cout << "Removing the first two elements from vectA & vectB" << endl;
	vectA.erase(vectA.begin(), vectA.begin() + 2);
	vectB.erase(vectB.begin(), vectB.begin() + 2);

	if (DEBUG)  cout_1d_vect(vectA);
	if (DEBUG)  cout_1d_vect(vectB);

	// Convert 1D to 2D
	vector<vector<short int>> A(rowA, vector<short int>(colA,0));
	vector<vector<short int>> B(rowB, vector<short int>(colB, 0));

	if (DEBUG2) cout_2d_vect(A);
	if (DEBUG2) cout_2d_vect(B);
	convert2d(vectA, &A, rowA, colA);
	convert2d(vectB, &B, rowB, colB);

	if (DEBUG2) cout_2d_vect(A);
	if (DEBUG2) cout_2d_vect(B);

	// Convert each matrix into the sparse format
	// I'll use the compressed sparse row with array/vector representation
	vector<short int> valueA;
	vector<short int> columnA;
	vector<short int> rowptrA(rowA);

	short int val;
	short int count;
	rowptrA.push_back(0);  // Init with 0
	for (short int r = 0; r < rowA; r++)
	{
		count = 0;
		for (short int c = 0; c < colA; c++)
		{
			val = A[r][c];
			if (DEBUG2) cout << val << " ";
			if (val != 0)
			{
				valueA.push_back(val);
				columnA.push_back(c);
				count++;
			}
		}
		rowptrA.at(r+1) = rowptrA.at(r) + count;
		if (DEBUG3) cout << rowptrA.at(r) << endl;
		if (DEBUG3) cout << rowptrA.at(r+1) + count  << endl;
		if (DEBUG2) cout << endl;
	}
	if (DEBUG2)
	{
		cout << "---------------------" << endl;
		cout_1d_vect(valueA);
		cout_1d_vect(columnA);
		cout_1d_vect(rowptrA);
	}

	// For B
	vector<short int> valueB;
	vector<short int> columnB;
	vector<short int> rowptrB(rowB);

	val;
	count = 0;
	rowptrB.push_back(count);  // Init with 0
	for (short int r = 0; r < rowB; r++)
	{
		count = 0;
		for (short int c = 0; c < colB; c++)
		{
			val = B[r][c];
			if (DEBUG2) cout << val << " ";
			if (val != 0)
			{
				valueB.push_back(val);
				columnB.push_back(c);
				count++;
			}
		}
		rowptrB.at(r + 1) = rowptrB.at(r) + count;
		if (DEBUG2) cout << endl;
	}
	if (DEBUG2)
	{
		cout_1d_vect(valueB);
		cout_1d_vect(columnB);
		cout_1d_vect(rowptrB);
	}

	// Multiply
	vector<vector<short int>> C(rowA, vector<short int>(colB, 0));
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colB; i++)
		{
			c[i][j] += valueA(i, columnA) * valueB(columnB);
		}
	}
}

string
solution(string matA, string matB)
{
	if (DEBUG)  cout << matA << endl;
	if (DEBUG)  cout << matB << endl;
	if (DEBUG)  cout << "--------------" << endl;

	vector<short int> vectA;
	vector<short int> vectB;

	vectA = str2short(matA);
	vectB = str2short(matB);

	if (DEBUG)  cout_1d_vect(vectA);
	if (DEBUG)  cout_1d_vect(vectB);
	
	multiply_sparse_matrix(vectA, vectB);

	string answer = "";
	return answer;
}

/*  Example Input
string A = "3 4 1 2 1 0 0 2 0 1 4 0 0 0";
string B = "4 2 0 0 5 0 0 0 0 1";
*/
int main()
{
	//string A = "3 3 3 0 2 2 3 4 0 0 3";
	string A = "4 4 0 0 0 0 5 8 0 0 0 0 3 0 0 6 0 0";
	string B = "4 2 0 0 5 0 0 0 0 1";

	solution(A, B);
}