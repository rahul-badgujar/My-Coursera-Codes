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
	void fastestRoute_v1(const Int &u, const Int &v)
	{
		// For Graph withouth -VE Weight Cycle
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		dist[u] = 0;
		bool flag = false;
		for (Int i = 1; i <= size - 1; i++)
		{
			flag = false;
			for (auto e : edges)
			{
				if (dist[e.v1] < MOD)
				{
					Int tDist = dist[e.v1] + eWeights[Edge::toString(e)];
					if (dist[e.v2] > tDist)
					{
						flag = true;
						dist[e.v2] = tDist;
						prev[e.v2] = e.v1;
					}
				}
			}
			if (!flag)
				break;
		}
		if (dist[v] == MOD)
		{
			logn("No Route Exist !");
		}
		else
		{
			log("Fastest Route : ");
			logn(dist[v]);
			vector<Int> path = retracePath(v, prev);
			path.push_back(v);
			log("Path : ");
			debVect(path);
		}
	}
	void fastestRoute_v2(const Int &u, const Int &v)
	{
		// For Graph with -VE Weight Cycle
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		dist[u] = 0;
		Int lastRelaxed = -1;
		for (Int i = 1; i <= size; i++)
		{
			lastRelaxed = -1;
			for (auto e : edges)
			{
				if (dist[e.v1] < MOD)
				{
					Int tDist = dist[e.v1] + eWeights[Edge::toString(e)];
					if (dist[e.v2] > tDist)
					{
						lastRelaxed = e.v2;
						dist[e.v2] = tDist;
						prev[e.v2] = e.v1;
					}
				}
			}
			if (lastRelaxed == -1)
				break;
		}
		if (lastRelaxed == -1)
		{
			if (dist[v] == MOD)
			{
				logn("No Route Exist !");
			}
			else
			{
				log("Fastest Route : ");
				logn(dist[v]);
				vector<Int> path = retracePath(v, prev);
				path.push_back(v);
				log("Path : ");
				debVect(path);
			}
		}
		else
		{
			logn("Negative Cycle Exists!");
			Int y = lastRelaxed;
			for (Int i = 1; i <= size; i++)
				y = prev[y];
			vector<Int> cyclePath;
			for (Int i = y;; i = prev[i])
			{
				cyclePath.push_back(i);
				if (i == y and cyclePath.size() > 1)
					break;
			}
			log("Cycle Path : ");
			debVect(cyclePath);
		}
	}
	void fastestRoute_v3(const Int &u, const Int &v)
	{
		// SPFA : Shortest Path Fast Algorithm
		// For Graph with -VE Weight Cycle
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		queue<Int> toRelax;
		vector<bool> isInQueue(size + 1, false);
		vector<Int> relaxCount(size + 1, 0);
		dist[u] = 0;
		toRelax.push(u);
		relaxCount[u] = 1;
		isInQueue[u] = true;
		bool hasCycle = false;
		while (!toRelax.empty() and !hasCycle)
		{
			Int r = toRelax.front();
			toRelax.pop();
			isInQueue[r] = false;
			for (auto i : vertices[r].adjList)
			{
				Int tDist = dist[r] + eWeights[Edge::toString(Edge(r, i))];
				if (dist[i] > tDist)
				{
					dist[i] = tDist;
					prev[i] = r;
					relaxCount[i]++;
					if (relaxCount[i] >= size)
					{
						hasCycle = true;
						break;
					}
					if (!isInQueue[i])
					{
						toRelax.push(i);
						isInQueue[i] = true;
					}
				}
			}
		}
		if (!hasCycle)
		{
			if (dist[v] == MOD)
			{
				logn("No Route Exist !");
			}
			else
			{
				log("Fastest Route : ");
				logn(dist[v]);
				vector<Int> path = retracePath(v, prev);
				path.push_back(v);
				log("Path : ");
				debVect(path);
			}
		}
		else
		{
			logn("Negative Cycle Exists!");
			Int y = toRelax.back();
			for (Int i = 1; i <= size; i++)
				y = prev[y];
			vector<Int> cyclePath;
			for (Int i = y;; i = prev[i])
			{
				cyclePath.push_back(i);
				if (i == y and cyclePath.size() > 1)
					break;
			}
			log("Cycle Path : ");
			debVect(cyclePath);
		}
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
	logn("Version 2 : ");
	g.fastestRoute_v2(x, y);
	logn("Version 3 : ");
	g.fastestRoute_v3(x, y);
	return 0;
}
