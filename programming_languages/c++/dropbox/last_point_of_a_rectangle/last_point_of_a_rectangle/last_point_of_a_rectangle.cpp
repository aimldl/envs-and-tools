// last_point_of_a_rectangle.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

void
cout_vect_vect(vector<vector<int> > v)
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
}

vector<int> solution(vector<vector<int> > v) {
	vector<int> ans;

	cout_vect_vect(v);

	return ans;
}

/*
	for (vector< vector<int> >::iterator itr_r = v.begin();
		itr_r != v.end();
		itr_r++
		)
	{
		for (vector<int>::iterator itr_c= itr_r.begin();
			itr_c != v.end();
			itr_c++
			)
		{

		}
	}


*/