#pragma once
#include <time.h>

//��������ģ��matlab��tictoc�࣬��λms
class TicToc
{
	clock_t ticTime;
public:
	TicToc();
	//��ʼ��ʱ
	void tic();

	//���ش��ϴο�ʼ��ʱ�����ڵ�ʱ���
	clock_t toc();

};

