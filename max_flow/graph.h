#pragma once
#include <iostream>
#include <vector>
#include <queue>

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

	AdjGraph(const AdjGraph& adjGraph) :
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

	Graph()
	{

	}

	Graph(const Graph& graph) :
		AdjGraph(graph)
	{

	}

	Graph(const AdjGraph& graph) :
		AdjGraph(graph)
	{

	}

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
	Route routeBFS(int s, int d)
	{
		if (s >= numV() || d >= numV())
		{
			cerr << "超出节点数量范围！" << endl;
		}
		vector<bool> searched(numV(), false);
		queue<int> b;
		Route route;
		vector<int>from(numV());
		searched[s] = true;
		b.push(s);
		while (!b.empty())
		{
			int v = b.front();
			b.pop();

			for (int i = 0; i < numV(); i++)
			{
				if (i != v && adjMatrix[v][i] > 0 && searched[i] == false)
				{
					searched[i] = true;
					from[i] = v;
					if (i == d)
					{
						while (i != s)
						{
							route.push_back(i);
							i = from[i];
						}
						route.push_back(i);
						reverse(route.begin(), route.end());
						return route;
					}
					b.push(i);
				}
			}

		}
		return route;
	}

	/*
	基于增广路径和Edmonds Karp的最大流算法
	章程2015010912010
	*/
public:
	Graph maxFlowEK(int s, int d)
	{
		Graph maxFlow(numV()), rNet(*this);

#ifdef DEBUG
		cout << "初始化的剩余网络：" << endl << rNet << endl;
		int rNum = 1;
#endif // DEBUG

		Route rRoute = rNet.routeBFS(s, d);
		while (rRoute.size() > 0)
		{
			int flow = rNet.getRouteFlow(rRoute);

			//向最大流图记录输送的流
			addFlow(maxFlow, rRoute, flow);

			//更新剩余网络
			refreshRNet(rNet, rRoute, flow);

#ifdef DEBUG
			cout << "############第" << rNum++ << "次增广############" << endl;
			cout << "增广容量：" << flow << endl;
			cout << "最大流网络：" << endl << maxFlow << endl;
			cout << "剩余网络：" << endl << rNet << endl;
#endif // DEBUG

			rRoute = rNet.routeBFS(s, d);
		}



		return maxFlow;
	}

protected:

	//获取某路径的流大小
	int getRouteFlow(Route r)
	{
		int flow = 0;
		if (r.size() > 1)
		{
			flow = adjMatrix[r[0]][r[1]];
			for (int i = 1; i < r.size() - 1; i++)
			{
				if (flow > adjMatrix[r[i]][r[i + 1]])
				{
					flow = adjMatrix[r[i]][r[i + 1]];
				}
			}
		}
		return flow;
	}

	//更新剩余网络
	//对剩余网络rNet
	//进行沿route路径的更新
	//增广容量为flow
	void refreshRNet(Graph& rNet, Route route, int flow)
	{
		if (route.size() > 1)
		{
			for (int i = 0; i < route.size() - 1; i++)
			{
				int s = route[i], d = route[i + 1];
				rNet[s][d] -= flow;
				rNet[d][s] += flow;
			}
		}
	}

	//向最大流图沿route输送flow单位的流
	void addFlow(Graph& flowGraph, Route route, int flow)
	{
		if (route.size() > 1)
		{
			for (int i = 0; i < route.size() - 1; i++)
			{
				int s = route[i], d = route[i + 1];
				int flowWeight = flowGraph[s][d] - flowGraph[d][s] + flow;
				if (flowWeight > 0)
				{
					flowGraph[s][d] = flowWeight;
					flowGraph[d][s] = 0;
				}
				else
				{
					flowGraph[s][d] = 0;
					flowGraph[d][s] = -flowWeight;
				}
			}
		}
	}

	/*
	基于Preflow Push/Push Relabel的最大流算法
	章程2015010912010
	END
	*/
public:

	Graph maxFlowPR(int s, int d)
	{
		Graph maxFlow(numV());
		vector<int> h(numV(), 0);




		return maxFlow;
	}

protected:

	/*
	基于Preflow Push/Push Relabel的最大流算法
	章程2015010912010
	END
	*/


};



