// strlen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"

#include <iostream>
#include <cstdio>
#include <cstring>

int main()
{
	char str[100];
	// Enter any string, e.g. "hello, world"
	scanf("%s", str);
	printf("strlen(%s)=%d\n", str, strlen(str));

	return 0;
}