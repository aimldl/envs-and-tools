// str2int.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
	string s = "3 4 1 2 1 0 0 2 0 1 4 0 0 0";
	string out;
	stringstream ss;

	ss << s;
	int x;
	while (ss >> out)
	{
		stringstream convert(out);
		convert >> x;
		printf("%d\n", x);
//		cout << x << endl;
	}
	return 0;
}

/* The following is a working code.
   To test, enter 
   1 2 33 10
   1
   2
   33
   10
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
	string s, out;
	stringstream ss;
	getline(cin, s);
	ss << s;
	int x;
	while (ss >> out)
	{
		stringstream convert(out);
		convert >> x;
		cout << x << endl;
	}
	return 0;
}
*/