/*
DCAB (CC.cpp)
문제: 정수 A,B,C,D 를 차례대로 입력받고, D,C,A,B 순으로 출력하는 프로그램을 작성해보자.
입력: 첫째 줄에 정수 A,B,C,D가 주어진다. ( A,B,C,D 는 100 이하의 정수 )
출력: 첫째 줄에 D, C, A, B 순으로 출력한다.
예제 입력: 1 6 3 2
예제 출력: 2 3 1 6
예제 입력: 9 1 2 3
예제 출력: 3 2 9 1
*/

#include <iostream>
using namespace std;

int main()
{
  int A,B,C,D;

  cin >> A >> B >> C >> D;
  cout << D << " " << C << " " << A << " " << B << " " << endl;  
    
  return 0;
}