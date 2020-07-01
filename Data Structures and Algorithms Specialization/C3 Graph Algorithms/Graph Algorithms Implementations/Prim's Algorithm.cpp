#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define INF (Int)1000000000001
#define uInt unsigned long long int
#define Int long long int

using namespace std;

typedef pair<Int, pair<Int, Int>> prim_pair;

template <typename T, typename U>
void debArr(T arr[], U n)
{
	for (U i = 0; i <= n - 1; i++)
	{
		logs(arr[i]);
	}
	log(endl);
}

template <typename T>
void debVect(vector<T> arr)
{
	for (auto i : arr)
	{
		logs(i);
	}
	log(endl);
}

class UnDirGraph
{
  private:
	class Vertex
	{
	  public:
		Int key;
		vector<Int> adjList;
		Vertex(const Int &k)
		{
			key = k;
		}
		Vertex(const Int &k, const Int &s)
		{
			key = k;
			adjList.reserve(s);
		}
	};
	class Edge
	{
	  public:
		Int v1, v2;
		Int cost;
		Edge()
		{
			v1 = v2 = cost = 0;
		}
		Edge(const Int &x, const Int &y)
		{
			v1 = x;
			v2 = y;
			cost = 0;
		}
		Edge(const Int &x, const Int &y, const Int &c)
		{
			v1 = x;
			v2 = y;
			cost = c;
		}
		static string toString(const Edge &e)
		{
			string s = to_string(e.v1) + " " + to_string(e.v2);
			return s;
		}
		static bool sortByCost(const Edge &e1, const Edge &e2)
		{
			return e1.cost < e2.cost;
		}
	};
	Int size;
	vector<Vertex> vertices;
	vector<Edge> edges;
	unordered_map<string, Int> eWeights;

	static vector<Int> retracePath(Int v, vector<Int> prev)
	{
		vector<Int> path;
		v = prev[v];
		while (v != -1)
		{
			path.push_back(v);
			v = prev[v];
		}
		reverse(path.begin(), path.end());
		return path;
	}

  public:
	UnDirGraph(const Int &n, const Int &m)
	{
		size = n;
		vertices.resize(size, Vertex(0, size));
		edges.resize(m);
		for (Int i = 0; i <= size - 1; i++)
		{
			vertices[i].key = i;
		}
	}
	const vector<Vertex> &getVertices() const
	{
		return vertices;
	}
	void markEdge(const Int &i, const Int &j, const Int &k)
	{
		vertices[i].adjList.push_back(j);
		Edge e(i, j, k);
		edges.push_back(e);
		eWeights[Edge::toString(e)] = k;
		vertices[j].adjList.push_back(i);
		Edge e2(j, i, k);
		edges.push_back(e2);
		eWeights[Edge::toString(e2)] = k;
	}
	void getMinSpanCost()
	{
		priority_queue<prim_pair, vector<prim_pair>, greater<prim_pair>> pq;
		vector<bool> marked(size, false);
		pq.push({0, {0, -1}});
		vector<pair<Int, Int>> tarEdges;
		tarEdges.reserve(size);
		Int cost = 0;
		while (!pq.empty())
		{
			prim_pair p = pq.top();
			pq.pop();
			Int vert = p.second.first;
			if (marked[vert])
				continue;
			marked[vert] = true;
			cost += p.first;
			Int par = p.second.second;
			tarEdges.push_back({par, vert});
			for (auto i : vertices[vert].adjList)
			{
				if (!marked[i])
				{
					Int c = eWeights[Edge::toString(Edge(vert, i))];
					pq.push({c, {i, vert}});
				}
			}
		}
		logs("Minimum Cost : ");
		logn(cost);
		logn("Targeted Edges : ");
		for (Int i = 1; i < tarEdges.size(); i++)
		{
			logs(tarEdges[i].first + 1);
			logn(tarEdges[i].second + 1);
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Input Vertices are 1-Based

	Int n, m;
	cin >> n >> m;
	UnDirGraph g(n, m);
	while (m--)
	{
		Int i, j, k;
		cin >> i >> j >> k;
		g.markEdge(--i, --j, k);
	}
	g.getMinSpanCost();
	return 0;
}
