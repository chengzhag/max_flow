#include "graph.h"
#include <iostream>

using namespace std;

int main()
{
	Graph g1(5);
	g1.addUV(0, 1, 6);
	g1.addUV(1, 2, 22);
	//g1.addUV(2, 3, 16);
	//g1.addUV(3, 4, 78);
	g1.addUV(1, 4, 10);
	g1.addUV(0, 4, 35);

	cout << "g1:" << endl << g1 << endl;

	//����BFS��С����·��
	auto route = g1.routeBFS(0, 3);
	cout << "��С����·��������" << route.size() - 1 << endl;
	cout << route << endl;


	return 0;
}