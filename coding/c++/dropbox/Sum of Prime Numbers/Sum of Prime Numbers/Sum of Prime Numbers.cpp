// Sum of Prime Numbers.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

//소수의 합
//문제 설명
//2부터 N까지의 모든 소수의 합을 구하세요.
//N이 7이라면{ 2,3,5,7 } = 17을 출력 하시면 됩니다.
//N의 범위는 2이상 10, 000, 000이하 입니다.
//효율성 테스트의 모든 시간 제한은 1초입니다.

// "에라토스네테스의 체"를 써서 푼다.

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;
#define DEBUG 1

long long
solution(int N)
{
	bool* is_checked = new bool [N+1];
	for (int i = 0; i <= N + 1; i++)
		is_checked[i] = false;

	int j, l;
	long long sum = 0;
	for (int i = 2; i <= N; i++)
	{
		j = N / i;
		if (!is_checked[i])
		{
			sum += i;
			for (int k = 1; k <= j; k++)
			{
				l = i * k;
				is_checked[l] = true;
			}
		}
	}
	long long answer = sum;
	return answer;
}

int
main()
{
	int N = 0;
	if (DEBUG)
	{
		N = 11;
		std::cout << solution(N) << std::endl;
	}

	return 0;
}

