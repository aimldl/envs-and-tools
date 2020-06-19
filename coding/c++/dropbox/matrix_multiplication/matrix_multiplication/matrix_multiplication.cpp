// matrix_multiplication.cpp 
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG 1

void
cout_2d_vect(vector<vector<int>> arr)
{
	cout << "(" << arr.size() << "x" << arr[0].size() << ") matrix" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>>
multiply(vector<vector<int>> arr1, vector<vector<int>> arr2)
{
	vector<vector<int>> answer;
	int val;

	if (DEBUG) cout_2d_vect(arr1);
	if (DEBUG) cout_2d_vect(arr2);

	// Assume arr1 & arr2 are the same size.
	if (arr1[0].size() != arr2.size()) cout << "Error: " << arr1.size() << "!=" << arr2[0].size() << endl;

	for (int i = 0; i < arr1.size(); i++)
	{
		vector<int> w;
		answer.push_back(w);
		for (int j = 0; j < arr2[0].size(); j++)
		{
			for (int k = 0; k < arr2.size(); k++)
			{
				val = arr1[i][k] + arr2[k][j];
				answer[i].push_back(val);
			}
		}
	}

	return answer;
}

int main()
{
	vector< vector<int> >  mat1{ {1,4}, {2,5}, {3,6} };
	vector< vector<int> >  mat2{ {7,8,9}, {10,11,12} };
	vector< vector<int> >  mat3;
	mat3 = multiply(mat1, mat2);

	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat3);

	/*
	vector< vector<int> >  mat4{ {1}, {2} };
	vector< vector<int> >  mat5{ {3}, {4} };
	vector< vector<int> >  mat6;

	mat6 = multiply(mat4, mat5);
	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat6);

	Error to add
	vector< vector<int> >  mat7{ {1,2}};
	vector< vector<int> >  mat8{ {3,4} };
	vector< vector<int> >  mat9;

	mat9 = multiply(mat7, mat8);
	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat9);
	*/

	return 0;
}

/* The following code is far from complete. I stopped it.
#include "pch.h"
#include <iostream>
using namespace std;

#define DEBUG 1

int main()
{
    std::cout << "Hello World!\n";
	int r_a, c_a;
	int r_b, c_b;

	int** mat_a = new int*[r_a];
	for (int i = 0; i < r_a; i++)
		mat_a[i] = new int[c_a];

	int** mat_b = new int*[r_b];
	for (int i = 0; i < r_b; i++)
		mat_b[i] = new int[c_b];

	int** mat_c = new int*[r_a];
	for (int i = 0; i < r_a; i++)
		mat_c[i] = new int[c_b];

	multiply( mat_a, mat_b )

	return 0;
}
*/