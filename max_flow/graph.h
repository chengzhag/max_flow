#pragma once
#include <iostream>
#include <vector>

using namespace std;

class AdjGraph
{
protected:
	vector<vector<int>> adjMatrix;
public:
	AdjGraph()
	{

	}

	AdjGraph(int numV)
	{
		setNumV(numV);
		clear();
	}

	AdjGraph(const AdjGraph& adjGraph):
		adjMatrix(adjGraph.adjMatrix)
	{
		
	}

	//设置节点数量
	void setNumV(int numV)
	{
		adjMatrix.resize(numV);
		for (int i = 0; i < numV; i++)
		{
			adjMatrix[i].resize(numV);
		}
	}

	//获取节点数量
	int numV() const
	{
		return adjMatrix.size();
	}


	//清零邻接矩阵
	void clear()
	{
		for (int i = 0; i < numV(); i++)
		{
			for (int j = 0; j < numV(); j++)
			{
				adjMatrix[i][j] = 0;
			}
		}
	}

	//添加有向边
	void addV(int s, int d, int w)
	{
		adjMatrix[s][d] = w;
	}

	//添加无向边
	void addUV(int v1, int v2, int w)
	{
		addV(v1, v2, w);
		addV(v2, v1, w);
	}

	//获取节点出度边权重
	//example: cout << "g1在[1,2]的权重是：" << endl << g1[1][2] << endl;
	vector<int>& const operator[](int s)
	{
		return adjMatrix[s];
	}

	//输出邻接矩阵
	friend ostream & operator<<(ostream &os, const AdjGraph &g)
	{
		int i = 0, j = 0;
		for (i = 0; i < g.numV() - 1; i++)
		{
			for (j = 0; j < g.numV(); j++)
			{
				os << g.adjMatrix[i][j] << "\t";
			}
			os << endl;
		}
		for (j = 0; j < g.numV(); j++)
		{
			os << g.adjMatrix[i][j] << "\t";
		}
		return os;
	}
};



