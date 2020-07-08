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
	void markEdge(const Int &i, const Int &j)
	{
		vertices[i].adjList.push_back(j);
		edges.push_back(Edge(i, j));
	}
	void getSCC(const Int &u, vector<bool> &isInStack, vector<Int> &preorder, vector<Int> &low, vector<vector<Int>> &result, stack<Int> &st)
	{
		static Int time = 0;
		preorder[u] = low[u] = ++time;
		st.push(u);
		isInStack[u] = true;
		for (auto i : vertices[u].adjList)
		{
			if (preorder[i] == -1)
			{
				getSCC(i, isInStack, preorder, low, result, st);
				low[u] = min(low[u], low[i]);
			}
			else if (isInStack[i])
			{
				low[u] = min(low[u], preorder[i]);
			}
		}
		if (low[u] == preorder[u])
		{
			Int w = -1;
			vector<Int> v;
			do
			{
				w = st.top();
				st.pop();
				isInStack[w] = false;
				v.push_back(w);
			} while (w != u);
			if (!v.empty())
				result.push_back(v);
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
		Int i, j;
		cin >> i >> j;
		g.markEdge(i - 1, j - 1);
	}
	vector<Int> low(n, INF), preorder(n, -1);
	stack<Int> st;
	vector<vector<Int>> scc;
	vector<bool> isInStack(n, false);
	for (Int i = 0; i < n; i++)
	{
		if (preorder[i] == -1)
		{
			g.getSCC(i, isInStack, preorder, low, scc, st);
		}
	}
	for (auto v : scc)
	{
		for (auto i : v)
		{
			logs(i + 1);
		}
		log('\n');
	}
	return 0;
}
