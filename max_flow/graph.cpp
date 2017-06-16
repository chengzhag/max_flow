#include "graph.h"

AdjGraph::AdjGraph(const AdjGraph& adjGraph) :
	adjMatrix(adjGraph.adjMatrix)
{

}

AdjGraph::AdjGraph(int numV)
{
	setNumV(numV);
	clear();
}

AdjGraph::AdjGraph()
{

}

void AdjGraph::setNumV(int numV)
{
	adjMatrix.resize(numV);
	for (int i = 0; i < numV; i++)
	{
		adjMatrix[i].resize(numV);
	}
}

int AdjGraph::numV() const
{
	return adjMatrix.size();
}

void AdjGraph::clear()
{
	for (int i = 0; i < numV(); i++)
	{
		for (int j = 0; j < numV(); j++)
		{
			adjMatrix[i][j] = 0;
		}
	}
}

void AdjGraph::addV(int s, int d, int w)
{
	adjMatrix[s][d] = w;
}

void AdjGraph::addUV(int v1, int v2, int w)
{
	addV(v1, v2, w);
	addV(v2, v1, w);
}

std::vector<int>& const AdjGraph::operator[](int s)
{
	return adjMatrix[s];
}

Graph::Graph(int numV, int numRandE, int weightRandMax) :
	AdjGraph(numV)
{
	for (int i = 0; i < numRandE; i++)
	{
		int s = rand() % numV, d = rand() % numV;
		while (adjMatrix[s][d] != 0)
		{
			s = rand() % numV, d = rand() % numV;
		}
		adjMatrix[s][d] = rand() % weightRandMax + 1;
	}
}

Graph::Graph(const AdjGraph& graph) :
	AdjGraph(graph)
{

}

Graph::Graph(const Graph& graph) :
	AdjGraph(graph)
{

}

Graph::Graph()
{

}

Graph::Route Graph::routeBFS(int s, int d)
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

Graph Graph::maxFlowEK(int s, int d)
{
	Graph maxFlow(numV()), rNet(*this);

#ifdef DEBUG
	cout << "初始化的剩余网络：" << endl << rNet << endl;
	int rNum = 1;
#endif // DEBUG

	Route rRoute = rNet.routeBFS(s, d);
	while (rRoute.size() > 0)
	{
		int cap = rNet._getRouteCap(rRoute);

		//向最大流图记录输送的流
		_addFlow(maxFlow, rRoute, cap);

		//更新剩余网络
		_refreshRNet(rNet, rRoute, cap);

#ifdef DEBUG
		cout << "############第" << rNum++ << "次增广############" << endl;
		cout << "增广容量：" << cap << endl;
		cout << "最大流网络：" << endl << maxFlow << endl;
		cout << "剩余网络：" << endl << rNet << endl;
#endif // DEBUG

		rRoute = rNet.routeBFS(s, d);
	}



	return maxFlow;
}

int Graph::_getRouteCap(const Route& r)
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

void Graph::_refreshRNet(Graph& rNet, const Route& route, int flow)
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

void Graph::_addFlow(Graph& flowGraph, int s, int d, int flow)
{
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

void Graph::_addFlow(Graph& flowGraph, const Route& route, int flow)
{
	if (route.size() > 1)
	{
		for (int i = 0; i < route.size() - 1; i++)
		{
			int s = route[i], d = route[i + 1];
			_addFlow(flowGraph, s, d, flow);
		}
	}
}

Graph Graph::maxFlowPR(int s, int d)
{
	//初始化
	Graph preFlow(numV()), rNet(*this);
	vector<int> h(numV(), 0), excess(numV(), 0);
	_initHeight(d, h);
	h[s] = numV();

	//判断是否有路径
	Route sd = routeBFS(s, d);
	if (sd.size() == 0)
	{
		return preFlow;
	}

#ifdef DEBUG
	cout << "初始化后的高度函数：" << endl;
	for (int i = 0; i < h.size() - 1; i++)
	{
		cout << h[i] << "\t";
	}
	cout << h[numV() - 1] << endl;
#endif // DEBUG

	//进行饱和推送
	for (int i = 0; i < numV(); i++)
	{
		if (i != s && rNet[s][i] > 0)
		{
			_pushFull(preFlow, rNet, excess, s, i);
		}
	}

#ifdef DEBUG
	cout << "初始化后的预流网络：" << endl << preFlow << endl;
	cout << "初始化后的剩余网络：" << endl << rNet << endl;
	cout << "初始化后的节点盈余：" << endl;
	for (int i = 0; i < excess.size() - 1; i++)
	{
		cout << excess[i] << "\t";
	}
	cout << excess[numV() - 1] << endl;

	int cNum = 1;
#endif // DEBUG

	//Push-Relabel
	while (hasExcess(excess, s, d))
	{
		//获取最大高度盈余点v
		int maxH = -1, v = 0;//最大高度可能为0
		for (int i = 0; i < numV(); i++)
		{
			if (i != s && i != d && excess[i] != 0 && maxH < h[i])
			{
				maxH = h[i];
				v = i;
			}
		}

		bool hasEvw = false;
		for (int i = 0; i < numV(); i++)
		{
			if (i != v && rNet[v][i] > 0 && h[v] == h[i] + 1)
			{
				_push(preFlow, rNet, excess, v, i);
				hasEvw = true;
				break;
			}
		}
		if (!hasEvw)
		{
			h[v]++;//Relabel
		}


#ifdef DEBUG
		cout << "############第" << cNum++ << "次循环############" << endl;
		cout << "最大高度盈余点：" << v << endl;
		cout << "最大高度：" << maxH << endl;
		cout << "预流网络：" << endl << preFlow << endl;
		cout << "剩余网络：" << endl << rNet << endl;
#endif // DEBUG
	}

	return preFlow;
}

void Graph::_initHeight(int d, vector<int>& h)
{
	if (d >= numV())
	{
		cerr << "超出节点数量范围！" << endl;
	}

	//反向s和d
	int s = d;

	//以反向的邻接矩阵做BFS
	int hop = 0;
	vector<bool> searched(numV(), false);
	queue<int> b;
	h[s] = 0;
	searched[s] = true;
	b.push(s);
	while (!b.empty())
	{
		hop++;
		int v = b.front();
		b.pop();

		for (int i = 0; i < numV(); i++)
		{
			//此处邻接矩阵的index反向
			if (i != v && adjMatrix[i][v] > 0 && searched[i] == false)
			{
				h[i] = hop;
				searched[i] = true;
				b.push(i);
			}
		}
	}
}

void Graph::_pushFull(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d)
{
	_addFlow(preFlow, s, d, rNet[s][d]);

	rNet[d][s] = rNet[s][d];
	rNet[s][d] = 0;

	//更新盈余
	excess[d] = _getExccess(preFlow, d);
}

int Graph::_getExccess(Graph& preFlow, int v)
{
	int excess = 0;
	for (int i = 0; i < numV(); i++)
	{
		if (i != v && preFlow[i][v] > 0)
		{
			excess += preFlow[i][v];
		}

		if (i != v && preFlow[v][i] > 0)
		{
			excess -= preFlow[v][i];
		}
	}
	return excess;
}

void Graph::_push(Graph& preFlow, Graph& rNet, vector<int>& excess, int s, int d)
{
	//计算顶点盈余
	int es = _getExccess(preFlow, s);

	//饱和推送或非饱和推送
	int flow = 0;
	if (es >= rNet[s][d])
	{
		flow = rNet[s][d];//饱和推送
	}
	else
	{
		flow = es;//非饱和推送
	}
	_addFlow(preFlow, s, d, flow);

	//更新剩余网络
	rNet[s][d] -= flow;
	rNet[d][s] += flow;

	//更新盈余
	excess[s] = _getExccess(preFlow, s);
	excess[d] = _getExccess(preFlow, d);
}

bool Graph::hasExcess(const vector<int>& v, int s, int d)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (i != s && i != d && v[i] != 0)
		{
			return true;
		}
	}
	return false;
}
