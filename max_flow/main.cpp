#include "graph.h"
#include <iostream>

using namespace std;
AdjGraph g1(5),g2(g1);

int main()
{
	g1.addV(1, 2, 5);
	g1.addUV(2, 4, 8);
	AdjGraph g3(g1);

	cout << "g1:" << endl << g1 << endl;
	cout << "g2:" << endl << g2 << endl;
	cout << "g3:" << endl << g3 << endl;
	cout << "g1在[1,2]的权重是：" << endl << g1[1][2] << endl;

	return 0;
}