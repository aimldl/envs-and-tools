/*
atoctob (EE.cpp)
문제: a부터 c까지 증가한 뒤, c-1부터 b까지 감소하는 과정을 출력해보자.
입력: 첫째 줄에 자연수 a,c,b가 공백을 가지고 주어진다. a는 c보다 작거나 같으며, c는 b보다 크게 입력된다. ( 1 <= a,b,c <= 1,000)
출력: 첫째 줄에 a부터 c까지의 자연수를 공백을 사이에 두고 차례대로 출력한 뒤, c-1부터 b까지의 자연수를 공백을 사이에 두고 차례대로 출력한다.
예제 입력: 2 5 3
예제 출력: 2 3 4 5 4 3
예제 입력: 1 7 2
예제 출력: 1 2 3 4 5 6 7 6 5 4 3 2
*/
#include <iostream>
using namespace std;

int main()
{
  int a, b, c;
  cin >> a >> c >> b;
  
  int diff;
  diff = c-a+1;
  
  for ( int i=a; i < a+diff; i++)
    cout << i << " ";
  
  diff = (c-1) - b +1;
  
  for ( int i=c-1; i > c-1-diff; i--)
    cout << i << " ";
  
  return 0;
}