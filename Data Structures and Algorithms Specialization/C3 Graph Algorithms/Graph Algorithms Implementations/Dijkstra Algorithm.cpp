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
#define MOD 1000000007
#define uInt unsigned long long int
#define Int long long int

using namespace std;

typedef pair<Int, Int> iPair;
typedef pair<Int, vector<Int>> RoutePair;

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

class DirGraph
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
		Edge()
		{
			v1 = v2 = 0;
		}
		Edge(const Int &x, const Int &y)
		{
			v1 = x;
			v2 = y;
		}
		static string toString(const Edge &e)
		{
			string s = to_string(e.v1) + " " + to_string(e.v2);
			return s;
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
	DirGraph(const Int &n, const Int &m)
	{
		size = n;
		vertices.resize(size + 1, Vertex(0, size));
		edges.resize(m);
		for (Int i = 1; i <= size; i++)
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
		Edge e(i, j);
		edges.push_back(e);
		eWeights[Edge::toString(e)] = k;
	}
	RoutePair fastestPath(const Int &u, const Int &v)
	{
		priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		vector<bool> minCorr(size + 1, false);
		dist[u] = 0;
		prev[u] = -1;
		pq.push({0, u});
		while (!pq.empty())
		{
			Int x = pq.top().second;
			pq.pop();
			minCorr[x] = true;
			for (auto i : vertices[x].adjList)
			{
				Int tDist = dist[x] + eWeights[Edge::toString(Edge(x, i))];
				if (!minCorr[i] and dist[i] > tDist)
				{
					dist[i] = tDist;
					prev[i] = x;
					pq.push({dist[i], i});
				}
			}
		}
		vector<Int> path;
		if (dist[v] != MOD)
		{
			path = retracePath(v, prev);
			path.push_back(v);
		}
		return {dist[v], path};
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Int n, m;
	cin >> n >> m;
	DirGraph g(n, m);
	while (m--)
	{
		Int i, j, k;
		cin >> i >> j >> k;
		g.markEdge(i, j, k);
	}
	Int x, y;
	cin >> x >> y;
	RoutePair d = g.fastestPath(x, y);
	if (d.first == MOD)
	{
		logn("No Path Exists !");
	}
	else
	{
		log("Fastest Path : ");
		logn(d.first);
		log("Path : ");
		debVect(d.second);
	}
	return 0;
}
