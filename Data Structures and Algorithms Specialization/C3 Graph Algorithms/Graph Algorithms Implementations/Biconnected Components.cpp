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
	void getBiconnComp(const Int &u, vector<Int> &preorder, vector<Int> &low, vector<vector<pair<Int, Int>>> &result, vector<Int> &parent, stack<pair<Int, Int>> &st)
	{
		static Int time = 0;
		preorder[u] = low[u] = ++time;
		Int childs = 0;
		for (auto i : vertices[u].adjList)
		{
			if (preorder[i] == -1)
			{
				childs++;
				parent[i] = u;
				st.push({u, i});
				getBiconnComp(i, preorder, low, result, parent, st);
				low[u] = min(low[u], low[i]);
				if ((parent[u] == -1 and childs > 1) or (parent[u] != -1 and low[i] >= preorder[u]))
				{
					vector<pair<Int, Int>> v;
					Int x, y;
					do
					{
						x = st.top().first;
						y = st.top().second;
						v.push_back(st.top());
						st.pop();
					} while (x != u and y != i);
					if (!v.empty())
						result.push_back(v);
				}
			}
			else if (i != parent[u] and preorder[i] < low[u])
			{
				low[u] = preorder[i];
				st.push({u, i});
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
	vector<Int> parent(n, -1), low(n, INF), preorder(n, -1);
	vector<vector<pair<Int, Int>>> bcc;
	stack<pair<Int, Int>> st;
	for (Int i = 0; i < n; i++)
	{
		if (preorder[i] == -1)
			g.getBiconnComp(i, preorder, low, bcc, parent, st);
		vector<pair<Int, Int>> v;
		while (!st.empty())
		{
			v.push_back(st.top());
			st.pop();
		}
		if (!v.empty())
			bcc.push_back(v);
	}
	for (auto v : bcc)
	{
		for (auto i : v)
		{
			cout << i.first + 1 << "-" << i.second + 1 << "  ";
		}
		log('\n');
	}
	return 0;
}

/* 
INP 1 :
6 6
1 4
4 3
3 5
5 2
3 6
5 6
*/
