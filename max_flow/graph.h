#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

//#define DEBUG

class AdjGraph
{
protected:
	vector<vector<int>> adjMatrix;
public:
	AdjGraph();

	AdjGraph(int numV);

	AdjGraph(const AdjGraph& adjGraph);

	//���ýڵ�����
	void setNumV(int numV);

	//��ȡ�ڵ�����
	int numV() const;


	//�����ڽӾ���
	void clear();

	//��������
	void addV(int s, int d, int w);

	//��������
	void addUV(int v1, int v2, int w);

	//��ȡ�ڵ���ȱ�Ȩ��
	//example: cout << "g1��[1,2]��Ȩ���ǣ�" << endl << g1[1][2] << endl;
	vector<int>& const operator[](int s);

	//����ڽӾ���
	friend ostream & operator<<(ostream &os, const AdjGraph &g)
	{
		if (g.numV() > 0)
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
		}

		return os;
	}
};

class Graph :public AdjGraph
{
protected:

public:

	Graph();

	Graph(const Graph& graph);

	Graph(const AdjGraph& graph);

	Graph(int numV, int numRandE, int weightRandMax);

	//����vector��·���࣬������<<�������������
	class Route :public vector<int>
	{
	public:
		friend ostream & operator<<(ostream &os, const Route &r)
		{
			if (r.size() > 0)
			{
				int i = 0;
				for (i = 0; i < r.size() - 1; i++)
				{
					os << r[i] << "->";
				}
				os << r[i];
			}
			return os;
		}
	};

	//����BFS����s��d����С����·��
	Route routeBFS(int s, int d);

	/*
	��������·����Edmonds Karp��������㷨
	�³�2015010912010
	*/
public:
	Graph maxFlowEK(int s, int d);

protected:

	//��ȡĳ·����������С
	int _getRouteCap(const Route& r);

	//����ʣ������
	//��ʣ������rNet
	//������route·���ĸ���
	//��������Ϊflow
	void _refreshRNet(Graph& rNet, const Route& route, int flow);

	//�������ͼ��route����flow��λ����
	void _addFlow(Graph& flowGraph, const Route& route, int flow);

	//�������ͼ��e(s,d)����flow��λ����
	void _addFlow(Graph& flowGraph, int s, int d, int flow);



	/*
	����Preflow Push/Push Relabel��������㷨
	�³�2015010912010
	*/
public:
	Graph maxFlowPR(int s, int d);

protected:

	//����BFS��ʼ��������s��dΪ����ǰs��d
	void _initHeight(int d, vector<int>& h);

	//��������e(s,d)
	void _pushFull(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d);

	//����ӯ��
	int _getExccess(Graph& preFlow, int v);

	//����e(s,d)
	void _push(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d);

	//vector�Ƿ��з���ֵ
	bool hasExcess(const vector<int>& v, int s, int d);

	/*
	����Preflow Push/Push Relabel��������㷨
	�³�2015010912010
	END
	*/



};



