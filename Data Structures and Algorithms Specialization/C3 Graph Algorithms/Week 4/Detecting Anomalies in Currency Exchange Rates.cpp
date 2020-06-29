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
	//bool hasCycle(const Int &u)
	//	{
	//		// For Graph with -VE Weight Cycle
	//		vector<Int> dist(size + 1, MOD);
	//		dist[u] = 0;
	//		Int lastRelaxed = -1;
	//		for (Int i = 1; i <= size; i++)
	//		{
	//			lastRelaxed = -1;
	//			for (auto e : edges)
	//			{
	//				if (dist[e.v1] != MOD)
	//				{
	//					Int tDist = dist[e.v1] + eWeights[Edge::toString(e)];
	//					if (dist[e.v2] > tDist)
	//					{
	//						lastRelaxed = e.v2;
	//						dist[e.v2] = tDist;
	//					}
	//				}
	//			}
	//			if (lastRelaxed == -1)
	//				return false;
	//		}
	//		if (lastRelaxed == -1)
	//			return false;
	//		else
	//			return true;
	//	}
	bool hasCycle_v2(const Int &u, vector<bool> &visit)
	{
		// Optimized Bellman Ford
		// For Graph with -VE Weight Cycle
		visit[u] = true;
		vector<Int> dist(size + 1, MOD);
		queue<Int> toRelax;
		vector<bool> isInQueue(size + 1, false);
		vector<Int> relaxCount(size + 1, 0);
		dist[u] = 0;
		toRelax.push(u);
		isInQueue[u] = true;
		relaxCount[u]++;
		while (!toRelax.empty())
		{
			Int r = toRelax.front();
			toRelax.pop();
			isInQueue[r] = false;
			for (auto i : vertices[r].adjList)
			{
				visit[i] = true;
				Int tDist = dist[r] + eWeights[Edge::toString(Edge(r, i))];
				if (dist[i] > tDist)
				{
					dist[i] = tDist;
					relaxCount[i]++;
					if (relaxCount[i] >= size)
					{
						return true;
					}
					if (!isInQueue[i])
					{
						toRelax.push(i);
						isInQueue[i] = true;
					}
				}
			}
		}
		return false;
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
	bool ans = false;
	vector<bool> visit(n + 1, false);
	for (Int i = 1; i <= n; i++)
	{
		if (!visit[i])
		{
			ans = ans or g.hasCycle_v2(i, visit);
			if (ans)
				break;
		}
	}
	log(ans);
	return 0;
}
