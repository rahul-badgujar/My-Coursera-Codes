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
		Edge e(i, j);
		edges.push_back(e);
		eWeights[Edge::toString(e)] = k;
	}
	void spfa_noCycle(const Int &u)
	{
		// SPFA : Shortest Path Fast Algorithm
		// For Graph without -VE Weight Cycle
		vector<Int> dist(size, INF);
		vector<Int> prev(size, -1);
		queue<Int> toRelax;
		vector<bool> isInQueue(size, false);
		dist[u] = 0;
		toRelax.push(u);
		isInQueue[u] = true;
		while (!toRelax.empty())
		{
			Int r = toRelax.front();
			toRelax.pop();
			isInQueue[r] = false;
			for (auto i : vertices[r].adjList)
			{
				Int tDist = dist[r] + eWeights[Edge::toString(Edge(r, i))];
				if (dist[i] > tDist)
				{
					dist[i] = max(-1 * INF, tDist);
					prev[i] = r;
					if (!isInQueue[i])
					{
						toRelax.push(i);
						isInQueue[i] = true;
					}
				}
			}
		}

		log("Source : ");
		logn(u);
		for (Int i = 0; i <= size - 1; i++)
		{
			log("Point ");
			log(i + 1);
			log(" has min path of ");
			logn(dist[i]);
		}
	}
	void spfa_withCycle(const Int &u)
	{
		// SPFA : Shortest Path Fast Algorithm
		// For Graph with -VE Weight Cycle
		vector<Int> dist(size, INF);
		vector<Int> prev(size, -1);
		queue<Int> toRelax;
		vector<bool> isInQueue(size, false);
		vector<Int> relaxCount(size, 0);
		dist[u] = 0;
		toRelax.push(u);
		isInQueue[u] = true;
		relaxCount[u]++;
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
					dist[i] = max(-1 * INF, tDist);
					prev[i] = r;
					relaxCount[i]++;
					if (relaxCount[i] >= size)
					{
						hasCycle = true;
					}
					if (!isInQueue[i])
					{
						toRelax.push(i);
						isInQueue[i] = true;
					}
					if (hasCycle)
						break;
				}
			}
		}
		if (hasCycle)
		{
			//logn("Negative Cycle Exists!");
			vector<bool> visited(size, false);
			while (!toRelax.empty())
			{
				Int x = toRelax.front();
				toRelax.pop();
				visited[x] = true;
				dist[x] = -1 * INF;
				for (auto i : vertices[x].adjList)
				{
					if (!visited[i])
						toRelax.push(i);
				}
			}
		}
		for (Int i = 0; i <= size - 1; i++)
		{
			if(dist[i]==INF)
				logn("*");
			else if(dist[i]==-1*INF)
				logn("-");
			else
				logn(dist[i]);
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
	DirGraph g(n, m);
	while (m--)
	{
		Int i, j, k;
		cin >> i >> j >> k;
		g.markEdge(--i, --j, k);
	}
	Int x;
	cin >> x;
	g.spfa_withCycle(--x);
	return 0;
}
