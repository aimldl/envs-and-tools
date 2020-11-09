// representative_numbers.cpp

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

//#define DEBUG 1
#define DEBUG 0

void
swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

void
bubble_sort(int* arr, int N)
{
	int b = N;  // bar
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < b - 1; j++)  // j < b-1
		{
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
		b--;
	}
}

int
get_most_freq_num(int* nums, int N);

int main() {

	ifstream ifs("representative_numbers-ex1.txt");
	// Input
	int N = 10;
	int* nums = new int[N];
	for (int i = 0; i < N; i++)
		ifs >> nums[i];

	int mean;
	int freq;

	// Mean
	mean = 0;
	for (int i = 0; i < N; i++)
	{
		mean += nums[i];
	}
	mean /= N;

	// Output
	cout << mean << endl;
	cout << get_most_freq_num(nums, N) << endl;

	return 0;
}

int
get_most_freq_num(int* nums, int N)
{
	bubble_sort(nums, N);

	// Find the frequency of each number
	int** arr = new int*[2];  //arr[0][i] : number, arr[1][i] : frequency
	for (int i = 0; i < 2; i++)
		arr[i] = new int[N];

	int ref   = nums[0];
	int count = 1;
	int j     = 0;
	for (int i = 1; i < N; i++)
	{
		if (ref == nums[i])
		{
			count++;
		}
		else
		{
			arr[0][j] = ref;
			arr[1][j] = count;

			ref = nums[i];
			count = 1;
			j++;
		}
	}
	arr[0][j] = ref;
	arr[1][j] = count;

	arr[0][j+1] = -1;
	arr[1][j+1] = -1;

	if ( DEBUG )
	{
		j = 0;
		while (arr[0][j] >= 0)
		{
			cout << arr[0][j] << " " << arr[1][j] << endl;
			j++;
		}
	}

	// Find the max frequency
	int max_freq = arr[1][0];
	int max_idx  = 0;
	j = 1;
	while (arr[0][j] >= 0)
	{
		if (max_freq < arr[1][j])
		{
			max_freq = arr[1][j];
			max_idx = j;
		}
		j++;
	}
	
	int num_wt_max_freq = arr[0][max_idx];

	return num_wt_max_freq;
}