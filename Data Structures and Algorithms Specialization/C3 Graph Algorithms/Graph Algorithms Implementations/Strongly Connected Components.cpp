#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define MOD 1000000007
#define uInt unsigned long long int
#define Int long long int

using namespace std;

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
		Int preClock, postClock;
		vector<Int> adjList;
		Vertex(const Int &k)
		{
			key = k;
			preClock = postClock = 0;
		}
		Vertex(const Int &k, const Int &s)
		{
			key = k;
			preClock = postClock = 0;
			adjList.reserve(s);
		}
		static bool ascPreClock(const Vertex &v1, const Vertex &v2)
		{
			return v1.preClock <= v2.preClock;
		}
		static bool ascPostClock(const Vertex &v1, const Vertex &v2)
		{
			return v1.postClock <= v2.postClock;
		}
		static bool descPreClock(const Vertex &v1, const Vertex &v2)
		{
			return v1.preClock >= v2.preClock;
		}
		static bool descPostClock(const Vertex &v1, const Vertex &v2)
		{
			return v1.postClock >= v2.postClock;
		}
	};
	Int size;
	vector<Vertex> vertices;
	vector<pair<Int, Int>> edges;
	vector<bool> visitLog;
	vector<bool> stRec;
	stack<Int> stUtil;
	Int clock;

	void preVisit(const Int &u)
	{
		vertices[u].preClock = clock++;
	}
	void postVisit(const Int &u)
	{
		vertices[u].postClock = clock++;
		stUtil.push(u);
	}
	void reverse()
	{
		for (Int i = 1; i <= size; i++)
		{
			vertices[i].adjList.clear();
		}
		for (auto e : edges)
		{
			vertices[e.second].adjList.push_back(e.first);
		}
	}

  public:
	DirGraph(const Int &n, const Int &m)
	{
		size = n;
		clock = 0;
		vertices.resize(size + 1, Vertex(0, size));
		for (Int i = 1; i <= size; i++)
		{
			vertices[i].key = i;
		}
		edges.reserve(m);
		visitLog.resize(size + 1, false);
		stRec.resize(size + 1, false);
	}
	const vector<Vertex> &getVertices() const
	{
		return vertices;
	}
	void markEdge(const Int &i, const Int &j)
	{
		vertices[i].adjList.push_back(j);
		edges.push_back({i, j});
	}
	void explore(const Int &u, pair<bool, bool> visits = {true, true})
	{
		if (!visitLog[u])
		{
			visitLog[u] = true;
			if (visits.first)
				preVisit(u);
			for (auto i : vertices[u].adjList)
			{
				if (!visitLog[i])
				{
					explore(i, visits);
				}
			}
			if (visits.second)
				postVisit(u);
		}
	}
	void DFS()
	{
		clock = 1;
		for (Int i = 1; i <= size; i++)
		{
			if (!visitLog[i])
			{
				explore(i);
			}
		}
		visitLog.assign(size + 1, false);
	}
	int countSCC()
	{
		DFS();
		reverse();
		Int count = 0;
		while (!stUtil.empty())
		{
			Int sink = stUtil.top();
			if (!visitLog[sink])
			{
				explore(sink, {false, false});
				count++;
			}
			stUtil.pop();
		}
		return count;
		/*
		NOTES :
			1. We can get the groups of SCC by using Group Vector
			   and unique ID for each group.
		*/
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
		Int i, j;
		cin >> i >> j;
		g.markEdge(i, j);
	}
	logn(g.countSCC());
	return 0;
}

/*

LINK :
Status: In Progress

*/