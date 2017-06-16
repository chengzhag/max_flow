#pragma once
#include <time.h>

//面向对象的模仿matlab的tictoc类，单位ms
class TicToc
{
	clock_t ticTime;
public:
	TicToc():
		ticTime(0)
	{

	}
	//开始计时
	void tic()
	{
		ticTime = clock();
	}

	//返回从上次开始计时到现在的时间差
	clock_t toc()
	{
		return clock() - ticTime;
	}

};

