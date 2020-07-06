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
	void markEdge(const Int &i, const Int &j)
	{
		vertices[i].adjList.push_back(j);
		edges.push_back(Edge(i, j));
		vertices[j].adjList.push_back(i);
		edges.push_back(Edge(j, i));
	}
	void getCutVertices(const Int &u, vector<bool> &visited, vector<Int> &preorder, vector<Int> &low, vector<bool> &result, vector<Int> &parent)
	{
		static Int time = 0;
		visited[u] = true;
		preorder[u] = low[u] = ++time;
		Int childs = 0;
		for (auto i : vertices[u].adjList)
		{
			if (!visited[i])
			{
				childs++;
				parent[i] = u;
				getCutVertices(i, visited, preorder, low, result, parent);
				low[u] = min(low[u], low[i]);
				if (parent[u] == -1 and childs > 1)
					result[u] = true;
				else if (parent[u] != -1 and low[i] >= preorder[u])
					result[u] = true;
			}
			else if (i != parent[u])
			{
				low[u] = min(low[u], preorder[i]);
			}
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
		Int i, j;
		cin >> i >> j;
		g.markEdge(--i, --j);
	}
	vector<Int> parent(n, -1), low(n, INF), preorder(n, 0);
	vector<bool> visited(n, false), isArtVertex(n, false);
	for (Int i = 0; i < n; i++)
	{
		if (!visited[i])
			g.getCutVertices(i, visited, preorder, low, isArtVertex, parent);
	}
	for (Int i = 0; i < n; i++)
	{
		if (isArtVertex[i])
			logs(i + 1);
	}
	return 0;
}
