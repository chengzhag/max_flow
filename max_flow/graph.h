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

	//设置节点数量
	void setNumV(int numV);

	//获取节点数量
	int numV() const;


	//清零邻接矩阵
	void clear();

	//添加有向边
	void addV(int s, int d, int w);

	//添加无向边
	void addUV(int v1, int v2, int w);

	//获取节点出度边权重
	//example: cout << "g1在[1,2]的权重是：" << endl << g1[1][2] << endl;
	vector<int>& const operator[](int s);

	//输出邻接矩阵
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

	//基于vector的路径类，重载了<<操作符便于输出
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

	//基于BFS计算s到d的最小跳数路径
	Route routeBFS(int s, int d);

	/*
	基于增广路径和Edmonds Karp的最大流算法
	章程2015010912010
	*/
public:
	Graph maxFlowEK(int s, int d);

protected:

	//获取某路径的容量大小
	int _getRouteCap(const Route& r);

	//更新剩余网络
	//对剩余网络rNet
	//进行沿route路径的更新
	//增广容量为flow
	void _refreshRNet(Graph& rNet, const Route& route, int flow);

	//向最大流图沿route输送flow单位的流
	void _addFlow(Graph& flowGraph, const Route& route, int flow);

	//向最大流图边e(s,d)输送flow单位的流
	void _addFlow(Graph& flowGraph, int s, int d, int flow);



	/*
	基于Preflow Push/Push Relabel的最大流算法
	章程2015010912010
	*/
public:
	Graph maxFlowPR(int s, int d);

protected:

	//反向BFS初始化跳数，s、d为反向前s、d
	void _initHeight(int d, vector<int>& h);

	//饱和推送e(s,d)
	void _pushFull(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d);

	//计算盈余
	int _getExccess(Graph& preFlow, int v);

	//推送e(s,d)
	void _push(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d);

	//vector是否含有非零值
	bool hasExcess(const vector<int>& v, int s, int d);

	/*
	基于Preflow Push/Push Relabel的最大流算法
	章程2015010912010
	END
	*/



};



