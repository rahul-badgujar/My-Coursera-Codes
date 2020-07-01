#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iomanip>
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

class UFDS
{
  public:
	vector<Int> parent, rank;
	UFDS(const Int &n)
	{
		parent.resize(n);
		rank.resize(n);
		for (Int i = 0; i <= n - 1; i++)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}
	Int find(const Int &x)
	{
		if (x != parent[x])
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	void unite(const Int &x, const Int &y)
	{
		Int xid = find(x);
		Int yid = find(y);
		if (xid != yid)
		{
			if (rank[xid] < rank[yid])
			{
				parent[xid] = yid;
			}
			else if (rank[xid] > rank[yid])
			{
				parent[yid] = xid;
			}
			else
			{
				parent[xid] = yid;
				rank[yid]++;
			}
		}
	}
};

class UnDirGraph
{
  private:
	class Vertex
	{
	  public:
		Int x, y;
		Vertex()
		{
			x = y = 0;
		}
		Vertex(const Int &a, const Int &b)
		{
			x = a;
			y = b;
		}
		double operator-(const Vertex &v1)
		{
			double dist = (v1.y - y) * (v1.y - y) + (v1.x - x) * (v1.x - x);
			return sqrt(dist);
		}
	};
	class Edge
	{
	  public:
		Int v1, v2;
		double cost;
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
		Edge(const Int &x, const Int &y, const double &c)
		{
			v1 = x;
			v2 = y;
			cost = c;
		}
		static bool sortByCost(const Edge &e1, const Edge &e2)
		{
			return e1.cost < e2.cost;
		}
	};
	Int size;
	vector<Vertex> vertices;
	vector<Edge> edges;

  public:
	UnDirGraph(const Int &n)
	{
		size = n;
		vertices.reserve(n);
	}
	void addVertex(const Int &x, const Int &y)
	{
		vertices.push_back(Vertex(x, y));
	}
	void markEdges()
	{
		for (Int i = 0; i < size; i++)
		{
			for (Int j = i + 1; j < size; j++)
			{
				edges.push_back(Edge(i, j, vertices[i] - vertices[j]));
			}
		}
	}
	double getMinSpanCost()
	{
		vector<Edge> edg(edges.begin(), edges.end());
		sort(edg.begin(), edg.end(), Edge::sortByCost);
		UFDS ds(size);
		double cost = 0;
		for (Int i = 0; i < edg.size(); i++)
		{
			if (ds.find(edg[i].v1) != ds.find(edg[i].v2))
			{
				cost += edg[i].cost;
				ds.unite(edg[i].v1, edg[i].v2);
			}
		}
		return cost;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Input Vertices are 1-Based

	Int n;
	cin >> n;
	UnDirGraph g(n);
	while (n--)
	{
		Int i, j;
		cin >> i >> j;
		g.addVertex(i, j);
	}
	g.markEdges();
	cout << fixed << setprecision(9) << g.getMinSpanCost();
	return 0;
}
