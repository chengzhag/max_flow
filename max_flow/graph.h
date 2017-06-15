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

class Graph :public AdjGraph
{
protected:
	
public:
	Graph()
	{

	}

	Graph(const Graph& graph):
		AdjGraph(graph)
	{

	}

	Graph(const AdjGraph& graph) :
		AdjGraph(graph)
	{

	}

	class Route:public vector<int>
	{
	public:
		friend ostream & operator<<(ostream &os, const Route &r)
		{
			int i = 0;
			for (i = 0; i < r.size() - 1; i++)
			{
				os << r[i] << "->";
			}
			os << r[i];
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
	}
};

