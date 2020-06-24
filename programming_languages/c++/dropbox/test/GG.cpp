/*
사각형 테두리 출력하기 (GG.cpp)
문제: 가로 a, 세로 b의 사각형 테두리를 출력하는 프로그램을 작성하여라. Input, Output의 예제를 참고한다. (단, 사각형 테두리 내부는 빈공간이다.)
입력: 첫째 줄에 자연수 a,b가 주어진다. (3≤a,b≤100)
출력: 다음 예제와 같이 사각형 테두리 모양으로 ‘*’을 출력한다.
예제 입력: 5 5
예제 출력
*****
*   *
*   *
*   *
*****
예제 입력: 4 9
예제 출력
****
*  *
*  *
*  *
*  *
*  *
*  *
*  *
****
*/
#include <iostream>
using namespace std;

void print_star(int width, int height, int level)
{
  if (level==0 || level==height-1)
  {
    for (int w=0; w<width; w++)
      cout << "*";
  }
  else
  {
    cout << "*";
    for (int w=0; w<width-2; w++)
      cout << " ";
    cout << "*";
  }
  cout << endl;
}

int main()
{
  int w, h;  // = a, b
  cin >> w >> h;
  
  for (int l=0; l < h; l++)
  {
    print_star(w,h,l);
  }
  return 0;
}
