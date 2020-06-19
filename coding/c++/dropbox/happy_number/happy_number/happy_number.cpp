// happy_number.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

#include <iostream>
#include <stack>
#include <unordered_set>
using namespace std;

#define DEBUG 1

stack<int>
get_digits(int dec, int d )
{
	int dividend = dec;
	int divisor  = d;
	int remainder;
	int temp;

	stack<int> digits_;

	int i = 0;
	while (dividend > 0)  // >0 means no number is left to compute
	{
		temp = dividend / divisor;
		remainder = dividend % divisor;
		digits_.push(remainder);
		i++;
		dividend = temp;
	}
	if (DEBUG) cout << "Stack size=" << digits_.size() << endl;

	return digits_;
}

int
get_squared_sum(stack<int> digits_)
{
	int val;
	int sum = 0;
	while (!digits_.empty())
	{
		if (DEBUG) cout << "top=" << digits_.top() << " ";
		val = digits_.top();
		sum += val * val;
		if (DEBUG) cout << "sum=" << sum << " ";
		digits_.pop();
	}
	if (DEBUG) cout << endl;

	return sum;
}

int solution(int n)
{
	int answer;

	if (DEBUG)  cout << "n=" << n << endl;
	int num = n;
	int num_max = (2 << 30) - 1;  // 1023 = (2 << 9) - 1;
	if (DEBUG)  cout << "num_max=" << num_max << endl;

	stack<int> digits;
	unordered_set<int> ban;  // For the terminal condition
	bool is_happy = true;

	int count = 0;
	do
	{
		digits = get_digits(num, 10);
		num    = get_squared_sum(digits);
		count++;

		if ( ban.count(num) )  // if in the ban list
		{
			is_happy = false;
			break;
		}
		ban.insert(num);

	} while ( num != 1 );  // num==1 is the happy number!

	if ( is_happy ) answer = count;
	else            answer = -1;
	
	return answer;
}

int main()
{
	cout << "Expecting 4: " << solution(19) << endl;
	cout << "------------" << endl;
	cout << "Expecting -1: " << solution(21) << endl;
}