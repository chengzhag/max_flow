#pragma once
#include <time.h>

//��������ģ��matlab��tictoc�࣬��λms
class TicToc
{
	clock_t ticTime;
public:
	TicToc():
		ticTime(0)
	{

	}
	//��ʼ��ʱ
	void tic()
	{
		ticTime = clock();
	}

	//���ش��ϴο�ʼ��ʱ�����ڵ�ʱ���
	clock_t toc()
	{
		return clock() - ticTime;
	}

};

