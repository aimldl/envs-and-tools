/*
정렬하기 (HH.cpp)
문제: N개의 숫자가 주어질 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.
입력: 첫 번째 줄에 숫자의 개수 N이 주어진다. ( 1 <= N <= 1,000 ) 두 번째 줄에 정렬해야 할 N개의 숫자가 주어진다.
출력: 첫 번째 줄에 N개의 숫자를 오름차순으로 정렬한 결과를 출력한다.
예제 입력
10
1 9 2 8 3 4 5 7 6 10
예제 출력
1 2 3 4 5 6 7 8 9 10
*/

#include <iostream>
using namespace std;

void
swap(int& a, int& b)
{
  int temp;

  temp = a;
  a    = b;
  b    = temp;
}

int
simple_sort(int* num_, int size_)
{
	for (int i = 0; i < size_; i++)
		cout << num_[i] << " ";
	cout << endl;

    // simple_sort
	for (int i = 0; i < size_ - 1; i++)
	{
		if (num_[i] < num_[i + 1])
			swap(num_[i], num_[i + 1]);
	}

	for (int i = 0; i < size_; i++)
		cout << num_[i] << " ";
	cout << endl;

	return num_[1];
}

int main()
{
  int N;  
  cin >> N;

  int* num = new int [N];
  for (int n=0; n<N; n++)
    cin >> num[n];
  
  simple_sort( num, N );
  
  return 0;
}

/*
class node
{
public:
  node* left_node;
  node* right_node;
private:
  int value;
};

class binary_tree
{
public:
  binary_tree();
  ~binay_tree();
private:
    
};
*/