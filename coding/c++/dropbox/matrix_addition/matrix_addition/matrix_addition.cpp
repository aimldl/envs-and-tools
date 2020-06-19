#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG 0

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
add(vector<vector<int>> arr1, vector<vector<int>> arr2)
{
	vector<vector<int>> answer;
	int val;

	if (DEBUG) cout_2d_vect(arr1);
	if (DEBUG) cout_2d_vect(arr2);

	// Assume arr1 & arr2 are the same size.

	for (int i = 0; i < arr1.size(); i++)
	{
		vector<int> w;
		answer.push_back(w);
		for (int j = 0; j < arr1[i].size(); j++)
		{
			val = arr1[i][j] + arr2[i][j];
			answer[i].push_back(val);
		}
	}

	return answer;
}

int main()
{
	vector< vector<int> >  mat1{ {1,2}, {2,3} };
	vector< vector<int> >  mat2{ {3,4}, {5,6} };
	vector< vector<int> >  mat3;
	mat3 = add(mat1, mat2);

	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat3);


	vector< vector<int> >  mat4{ {1}, {2} };
	vector< vector<int> >  mat5{ {3}, {4} };
	vector< vector<int> >  mat6;

	mat6 = add(mat4, mat5);
	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat6);

	/* Error to add 
	vector< vector<int> >  mat7{ {1,2}};
	vector< vector<int> >  mat8{ {3,4} };
	vector< vector<int> >  mat9;

	mat9 = add(mat7, mat8);
	if (DEBUG) cout << "answer:" << endl;
	if (DEBUG) cout_2d_vect(mat9);
	*/

	return 0;
}