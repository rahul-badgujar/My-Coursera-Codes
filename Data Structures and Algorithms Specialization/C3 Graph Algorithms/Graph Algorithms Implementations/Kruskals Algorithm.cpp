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

class UFDS
{
  public:
    vector<Int> parent, rank;
    UFDS(const Int &n)
    {
        parent.resize(n);
        rank.resize(n);
        for (Int i = 0; i <= n-1; i++)
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
			v1 = v2 = cost= 0;
		}
		Edge(const Int &x, const Int &y)
		{
			v1 = x;
			v2 = y;
			cost=0;
		}
		Edge(const Int &x, const Int &y,const Int &c)
		{
			v1 = x;
			v2 = y;
			cost=c;
		}
		static string toString(const Edge &e)
		{
			string s = to_string(e.v1) + " " + to_string(e.v2);
			return s;
		}
		static bool sortByCost(const Edge &e1,const Edge &e2)
		{
			return e1.cost<e2.cost;
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
		Edge e(i, j,k);
		edges.push_back(e);
		eWeights[Edge::toString(e)] = k;
		vertices[j].adjList.push_back(i);
		Edge e2(j,i,k);
		edges.push_back(e2);
		eWeights[Edge::toString(e2)] = k;
	}
	Int getMinSpanCost()
	{
		vector<Edge> edg(edges.begin(),edges.end());
		sort(edg.begin(),edg.end(),Edge::sortByCost);
		UFDS ds(size);
		Int cost=0;
		for(auto e:edg)
		{
			if(ds.find(e.v1)!=ds.find(e.v2))
			{
				cost+=e.cost;
				ds.unite(e.v1,e.v2);
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

	Int n, m;
	cin >> n >> m;
	UnDirGraph g(n, m);
	while (m--)
	{
		Int i, j, k;
		cin >> i >> j >> k;
		g.markEdge(--i, --j, k);
	}
	logn(g.getMinSpanCost());
	return 0;
}
