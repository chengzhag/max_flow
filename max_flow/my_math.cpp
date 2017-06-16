#include "my_math.h"


TicToc::TicToc() :
	ticTime(0)
{

}

void TicToc::tic()
{
	ticTime = clock();
}

clock_t TicToc::toc()
{
	return clock() - ticTime;
}
