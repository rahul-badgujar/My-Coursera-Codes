#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
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

class UnDirGraph
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
	vector<bool> visitLog;
	vector<bool> stRec;
	stack<Int> stUtil;
	vector<Int> color;
	Int clock;

	void preVisit(const Int &u)
	{
		vertices[u].preClock = clock++;
	}
	void postVisit(const Int &u)
	{
		vertices[u].postClock = clock++;
	}

  public:
	UnDirGraph(const Int &n, const Int &m)
	{
		size = n;
		clock = 0;
		vertices.resize(size + 1, Vertex(0, size));
		for (Int i = 1; i <= size; i++)
		{
			vertices[i].key = i;
		}
		visitLog.resize(size + 1, false);
		stRec.resize(size + 1, false);
		color.resize(size + 1, -1);
	}
	const vector<Vertex> &getVertices() const
	{
		return vertices;
	}
	void markEdge(const Int &i, const Int &j)
	{
		vertices[i].adjList.push_back(j);
		vertices[j].adjList.push_back(i);
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
	bool BFS(const Int &u)
	{
		queue<Int> q;
		color[u] = 0;
		q.push(u);
		while (!q.empty())
		{
			Int x = q.front();
			q.pop();
			for (auto i : vertices[x].adjList)
			{
				if (color[i] == -1)
				{
					q.push(i);
					color[i] = !color[x];
				}
				else if (color[i] == color[x])
				{
					return false;
				}
			}
		}
		return true;
	}
	bool checkBipirate()
	{
		return BFS(1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Int n, m;
	cin >> n >> m;
	UnDirGraph g(n, m);
	while (m--)
	{
		Int i, j;
		cin >> i >> j;
		g.markEdge(i, j);
	}
	logn(g.checkBipirate());
	return 0;
}
