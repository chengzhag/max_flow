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

	//���ýڵ�����
	void setNumV(int numV)
	{
		adjMatrix.resize(numV);
		for (int i = 0; i < numV; i++)
		{
			adjMatrix[i].resize(numV);
		}
	}

	//��ȡ�ڵ�����
	int numV() const
	{
		return adjMatrix.size();
	}


	//�����ڽӾ���
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

	//��������
	void addV(int s, int d, int w)
	{
		adjMatrix[s][d] = w;
	}

	//��������
	void addUV(int v1, int v2, int w)
	{
		addV(v1, v2, w);
		addV(v2, v1, w);
	}

	//��ȡ�ڵ���ȱ�Ȩ��
	//example: cout << "g1��[1,2]��Ȩ���ǣ�" << endl << g1[1][2] << endl;
	vector<int>& const operator[](int s)
	{
		return adjMatrix[s];
	}

	//����ڽӾ���
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



