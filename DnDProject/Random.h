#pragma once
#include <Windows.h>

class Random
{
public:
	static int getRandomInt(int min, int max)
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		srand(st.wMilliseconds);
		Sleep(5);
		return rand() % (max + 1) + min;
	}
};

