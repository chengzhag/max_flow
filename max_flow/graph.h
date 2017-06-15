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
	Route routeBFS(int s, int d)
	{
		if (s >= numV() || d >= numV())
		{
			cerr << "�����ڵ�������Χ��" << endl;
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
	��������·����Edmonds Karp��������㷨
	�³�2015010912010
	*/
public:
	Graph maxFlowEK(int s, int d)
	{
		Graph maxFlow(numV()), rNet(*this);

#ifdef DEBUG
		cout << "��ʼ����ʣ�����磺" << endl << rNet << endl;
		int rNum = 1;
#endif // DEBUG

		Route rRoute = rNet.routeBFS(s, d);
		while (rRoute.size() > 0)
		{
			int flow = rNet.getRouteFlow(rRoute);

			//�������ͼ��¼���͵���
			addFlow(maxFlow, rRoute, flow);

			//����ʣ������
			refreshRNet(rNet, rRoute, flow);

#ifdef DEBUG
			cout << "############��" << rNum++ << "������############" << endl;
			cout << "����������" << flow << endl;
			cout << "��������磺" << endl << maxFlow << endl;
			cout << "ʣ�����磺" << endl << rNet << endl;
#endif // DEBUG

			rRoute = rNet.routeBFS(s, d);
		}



		return maxFlow;
	}

protected:

	//��ȡĳ·��������С
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

	//����ʣ������
	//��ʣ������rNet
	//������route·���ĸ���
	//��������Ϊflow
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

	//�������ͼ��route����flow��λ����
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
	����Preflow Push/Push Relabel��������㷨
	�³�2015010912010
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
	����Preflow Push/Push Relabel��������㷨
	�³�2015010912010
	END
	*/


};



