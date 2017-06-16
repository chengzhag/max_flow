#include "graph.h"
#include "my_math.h"
#include <iostream>
#include <time.h>

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



	////����BFS��С����·��
	//cout << "##########����BFS��С����·��##########" << endl;
	//auto route = g1.routeBFS(0, 3);
	//cout << "��С����·��������" << route.size() - 1 << endl;
	//cout << route << endl;


	//����EK�����
	cout << "##########����EK�����##########" << endl;
	timer.tic();
	Graph maxFlow1 = g1.maxFlowEK(0, 3);
	cout << "��ʱ��" << timer.toc() << "ms" << endl;
	cout << "��������磺" << endl << maxFlow1 << endl;


	//����PR�����
	cout << "##########����PR�����##########" << endl;
	timer.tic();
	Graph maxFlow2 = g1.maxFlowPR(0, 3);
	cout << "��ʱ��" << timer.toc() << "ms" << endl;
	cout << "��������磺" << endl << maxFlow2 << endl;

	//��EK��PR����ʱ�����
	int numVS = 5, numVE = 20;//�ڵ�������Χ
	float numEratioS = 0.2, numEratioE = 0.5;//������ڵ�����ƽ���ı�����Χ
	int numG = 20, avT = 10;

	cout << "##########��EK��PR����ʱ�����##########" << endl;
	cout << "�ڵ�������" << numVS << "��" << numVE << endl;
	cout << "������ڵ�����ƽ���ı�����" << numEratioS << "��" << numEratioE << endl;
	cout << "ÿ�ֲ�������" << numG << "��ͼ���в���" << endl;
	cout << "ÿ��ͼ����" << avT << "�β���" << endl;


	for (int numV = numVS; numV < numVE; numV++)
	{
		int numES = numV*numV* numEratioS + 1;//�����ķ�Χ
		int numEE = numV*numV* numEratioE + 1;
		for (int numE = numES; numE < numEE; numE++)
		{
			//��ÿ������������numG��ͼ��������

			double ekT = 0, prT = 0;//ͳ��numG��ͼ��ƽ��ʱ��

			for (int gNum = 0; gNum < numG; gNum++)
			{
				Graph g(numV, numE, numV);//�Խڵ�������Ϊ��Ȩ���Ͻ�
				//������ͼ����0->1������
				while (g.routeBFS(0, 1).size() == 0)
				{
					g = Graph(numV, numE, numV);//���û��0->��·������������ͼ
				}

				//����avT�ε�ʱ�䣬ȡƽ��ʱ��

				//��EK����ʱ�����
				timer.tic();
				for (int nowTime = 0; nowTime < avT; nowTime++)
				{
					g.maxFlowEK(0, 1);
				}
				ekT += (double)timer.toc() / avT;

				//��PR����ʱ�����
				timer.tic();
				for (int nowTime = 0; nowTime < avT; nowTime++)
				{
					g.maxFlowPR(0, 1);
				}
				prT += (double)timer.toc() / avT;
			}

			ekT /= numG;
			prT /= numG;
			cout << numV << "���ڵ�" << numE
				<< "���ߵ�ͼ��EKƽ����ʱ" << ekT
				<< "ms��PRƽ����ʱ" << prT << "ms" << endl;
		}
	}


	return 0;
}