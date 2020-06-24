/*
A 출력하기 (FF.cpp)
문제: n층의 A를 출력하는 프로그램을 작성하여라. Input, Output의 예제를 참고한다. (단, n은 항상 홀수만 주어진다.)
입력: 첫째 줄에 자연수이며, 홀수인 n이 주어진다. (5≤n≤100)
출력: 다음 예제와 같이 A 모양으로 ‘*’을 출력한다.
예제 입력: 5
예제 출력
    *
   * *
  *****
 *     *
*       *
예제 입력: 7
예제 출력
      *
     * *
    *   *
   *******
  *       *
 *         *
*           * 
*/

#include <iostream>
#include <cmath>
using namespace std;

void print_star(int height, int level)
{
	int leading_space = height - level;
	int middle_space = 2 * (level - 2) + 1;
	int median = (int)ceil((double)height / 2.0);

	for (int i = 0; i < leading_space; i++)
		cout << " ";

	if (level==1)
		cout << "*" << endl;
	else if (level == median)
	{
		cout << "*";
		for (int i = 0; i < middle_space; i++)
			cout << "*";
		cout << "*" << endl;
	}
	else
	{
		cout << "*";
		for (int i = 0; i < middle_space; i++)
			cout << " ";
		cout << "*" << endl;
	}
}

int main()
{
  int n;
  cin >> n;
  
  int h = n;
  for (int l=1; l<h+1; l++)
  {
    print_star( h,l );
  }
  
  return 0;
}