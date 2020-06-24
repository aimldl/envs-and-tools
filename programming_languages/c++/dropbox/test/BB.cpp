// BB.cpp
// A + B - C (BB.cpp)
// 문제: 세 수 A,B,C를 입력받고, A + B - C를 출력하는 프로그램을 작성해보자.
// 입력: 첫째 줄에 정수 A,B,C가 주어진다. ( A,B,C는 100 이하의 정수 )
// 출력: 첫째 줄에 A + B - C를 출력한다.
// 예제 입력: 5 6 3
// 예제 출력: 8

#include <iostream>
using namespace std;

int main()
{
  int A, B, C;
  int eq;
  
  cin >> A >> B >> C;
  eq = A + B - C;
  cout << eq << endl;

  return 0;
}