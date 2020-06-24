/*
세 개의 숫자 중 중간값 찾기 (DD.cpp)
문제: 3 개의 정수가 주어질 때, 이 중 중간값을 찾는 프로그램을 작성하여라.  
입력: 첫째 줄에 3개의 정수a,b,c 가 주어진다. (0≤a,b,c≤10,000)
출력: 첫째 줄에 a,b,c 중 중간값을 출력한다.
예제 입력: 10 2 5
예제 출력: 5
예제 입력: 3 7 7
예제 출력: 7
*/

#include <iostream>
using namespace std;

#include <iostream>
using namespace std;

void
swap(int& a, int& b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
}

int
get_median(int* num_, int size_)
{
/*
	for (int i = 0; i < size_; i++)
		cout << num_[i] << " ";
	cout << endl;
*/
    // simple_sort
	for (int i = 0; i < size_ - 1; i++)
	{
		if (num_[i] < num_[i + 1])
			swap(num_[i], num_[i + 1]);
	}
/*
	for (int i = 0; i < size_; i++)
		cout << num_[i] << " ";
	cout << endl;
*/
	return num_[1];
}

int main()
{
	int size = 3;
	int* num = new int[size];
	for (int i = 0; i < size; i++)
		cin >> num[i];

	cout << get_median(num, size);

	return 0;
}

/*
  int a, b, c;
  int t;
  
  cin >> a >> b >> c;

  // Swap a & b if b is larger. 
  
  if ( c > a )
  {
    t = c;
    c = a;
    c = t;
  }
  
  if ( b > a )
  {
    t = b;
    b = a;
    a = t;
  }
  if ( c < b )
  {
    t = c;
    c = b;
    b = t;
  }
  cout << b << endl;  
*/
