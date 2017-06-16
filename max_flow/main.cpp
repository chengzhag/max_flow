#include "graph.h"
#include "my_math.h"
#include <iostream>

using namespace std;

int main()
{
	TicToc timer;
	//Graph g1(4);
	//g1.addV(0, 1, 20);
	//g1.addV(1, 3, 10);
	//g1.addV(0, 2, 10);
	//g1.addV(1, 2, 30);
	//g1.addV(2, 3, 20);
	Graph g1(7, 30, 30);

	cout << "g1:" << endl << g1 << endl;


	
	////测试BFS最小跳数路径
	//cout << "##########测试BFS最小跳数路径##########" << endl;
	//auto route = g1.routeBFS(0, 3);
	//cout << "最小跳数路径跳数：" << route.size() - 1 << endl;
	//cout << route << endl;

	
	//测试EK最大流
	cout << "##########测试EK最大流##########" << endl;
	timer.tic();
	Graph maxFlow1 = g1.maxFlowEK(0, 3);
	cout << "用时：" << timer.toc() << "ms" << endl;
	cout << "最大流网络：" << endl << maxFlow1 << endl;
	
	
	//测试PR最大流
	cout << "##########测试PR最大流##########" << endl;
	timer.tic();
	Graph maxFlow2 = g1.maxFlowPR(0, 3);
	cout << "用时：" << timer.toc() << "ms" << endl;
	cout << "最大流网络：" << endl << maxFlow2 << endl;
	

	return 0;
}