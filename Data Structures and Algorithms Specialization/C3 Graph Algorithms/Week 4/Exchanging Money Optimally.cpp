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
	//	void fastestRoute_v1(const Int &u, const Int &v)
	//	{
	//		// For Graph withouth -VE Weight Cycle
	//		vector<Int> dist(size + 1, MOD);
	//		vector<Int> prev(size + 1, -1);
	//		dist[u] = 0;
	//		bool flag = false;
	//		for (Int i = 1; i <= size - 1; i++)
	//		{
	//			flag = false;
	//			for (auto e : edges)
	//			{
	//				if (dist[e.v1] != MOD)
	//				{
	//					Int tDist = dist[e.v1] + eWeights[Edge::toString(e)];
	//					if (dist[e.v2] > tDist)
	//					{
	//						flag = true;
	//						dist[e.v2] = tDist;
	//						prev[e.v2] = e.v1;
	//					}
	//				}
	//			}
	//			if (!flag)
	//				break;
	//		}
	//		if (dist[v] == MOD)
	//		{
	//			logn("No Route Exist !");
	//		}
	//		else
	//		{
	//			log("Fastest Route : ");
	//			logn(dist[v]);
	//			vector<Int> path = retracePath(v, prev);
	//			path.push_back(v);
	//			log("Path : ");
	//			debVect(path);
	//		}
	//	}
	void fastestRoute_v2(const Int &u)
	{
		// For Graph with -VE Weight Cycle
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		dist[u] = 0;
		queue<Int> q;
		for (Int i = 1; i <= size; i++)
		{
			bool flag = false;
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
						if (i == size)
							q.push(e.v2);
					}
				}
			}
			if (!flag)
				break;
		}
		vector<bool> visit(size + 1, false);
		while (!q.empty())
		{
			Int x = q.front();
			q.pop();
			visit[x] = true;
			dist[x] = -1 * MOD;
			for (auto i : vertices[x].adjList)
			{
				if (!visit[i])
					q.push(i);
			}
		}
		for (Int i = 1; i <= size; i++)
		{
			if (dist[i] == MOD)
				logn('*');
			else if (dist[i] == -1 * MOD)
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

	Int n, m;
	cin >> n >> m;
	DirGraph g(n, m);
	while (m--)
	{
		Int i, j, k;
		cin >> i >> j >> k;
		g.markEdge(i, j, k);
	}
	Int x;
	cin >> x;
	g.fastestRoute_v2(x);
	return 0;
}
