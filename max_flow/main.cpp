#include "graph.h"
#include "my_math.h"
#include <iostream>
#include <time.h>
#include <fstream>

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
	Graph g1(7, 10, 30);

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

	//对EK和PR进行时间测试
	//开启文件进行记录
	ofstream outFile;
	outFile.open("测试数据.txt");
	if (!outFile)
	{
		cerr << "打开输入'测试数据.txt'文件出错！" << endl;
		return 1;
	}

	int numVS = 5, numVE = 20;//节点数量范围
	float numEratioS = 1.2, numEratioE = 5;//边数与节点数量的比例范围
	int numG = 10, avT = 10;

	cout << "##########对EK和PR进行时间测试##########" << endl;
	cout << "节点数量从" << numVS << "到" << numVE << endl;
	cout << "边数与节点数量的比例从" << numEratioS << "到" << numEratioE << endl;
	cout << "每种参数生成" << numG << "个图进行测试" << endl;
	cout << "每个图进行" << avT << "次测试" << endl;

	outFile << "##########对EK和PR进行时间测试##########" << endl;
	outFile << "节点数量从" << numVS << "到" << numVE << endl;
	outFile << "边数与节点数量的比例从" << numEratioS << "到" << numEratioE << endl;
	outFile << "每种参数生成" << numG << "个图进行测试" << endl;
	outFile << "每个图进行" << avT << "次测试" << endl;
	outFile << endl << "节点数\t边数\tEK用时\tPR用时" << endl;


	for (int numV = numVS; numV < numVE; numV++)
	{
		int numES = numV* numEratioS + 1;//边数的范围
		int numEE = numV* numEratioE + 1;
		for (int numE = numES; numE < numEE; numE++)
		{
			//对每种情况随机生成numG个图用作测试

			double ekT = 0, prT = 0;//统计numG个图的平均时间

			for (int gNum = 0; gNum < numG; gNum++)
			{
				Graph g(numV, numE, numV);//以节点数量作为边权的上界
				//对所有图都以0->1做测试
				while (g.routeBFS(0, 1).size() == 0)
				{
					g = Graph(numV, numE, numV);//如果没有0->的路径，重新生成图
				}

				//测试avT次的时间，取平均时间

				//对EK进行时间测试
				timer.tic();
				for (int nowTime = 0; nowTime < avT; nowTime++)
				{
					g.maxFlowEK(0, 1);
				}
				ekT += (double)timer.toc() / avT;

				//对PR进行时间测试
				timer.tic();
				for (int nowTime = 0; nowTime < avT; nowTime++)
				{
					g.maxFlowPR(0, 1);
				}
				prT += (double)timer.toc() / avT;
			}

			ekT /= numG;
			prT /= numG;
			cout << numV << "个节点"
				<< numE << "条边的图下EK平均用时"
				<< ekT << "ms，PR平均用时"
				<< prT << "ms" << endl;
			outFile << numV << "\t" 
				<< numE << "\t"
				<< ekT << "\t" 
				<< prT << endl;
		}
	}


	return 0;
}