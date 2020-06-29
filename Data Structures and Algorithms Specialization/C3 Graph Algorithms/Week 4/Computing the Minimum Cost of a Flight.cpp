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
	vector<vector<Int>> weights;

	void preVisit(const Int &u)
	{
		vertices[u].preClock = clock++;
	}
	void postVisit(const Int &u)
	{
		vertices[u].postClock = clock++;
	}
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
		clock = 0;
		vertices.resize(size + 1, Vertex(0, size));
		for (Int i = 1; i <= size; i++)
		{
			vertices[i].key = i;
		}
		visitLog.resize(size + 1, false);
		stRec.resize(size + 1, false);
		color.resize(size + 1, -1);
		weights.resize(size + 1);
		for (Int i = 0; i <= size; i++)
		{
			weights[i].resize(size + 1, 0);
		}
	}
	const vector<Vertex> &getVertices() const
	{
		return vertices;
	}
	void markEdge(const Int &i, const Int &j, const Int &k)
	{
		vertices[i].adjList.push_back(j);
		weights[i][j] = k;
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
	RoutePair fastestPath(const Int &u, const Int &v)
	{
		priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
		vector<Int> dist(size + 1, MOD);
		vector<Int> prev(size + 1, -1);
		vector<bool> minCorr(size + 1, false);
		dist[u] = 0;
		prev[u] = -1;
		pq.push({0, u});
		while (!pq.empty())
		{
			Int x = pq.top().second;
			pq.pop();
			minCorr[x] = true;
			for (auto i : vertices[x].adjList)
			{
				if (!minCorr[i] and dist[i] > dist[x] + weights[x][i])
				{
					dist[i] = dist[x] + weights[x][i];
					prev[i] = x;
					pq.push({dist[i], i});
				}
			}
		}
		vector<Int> path;
		if(dist[v]!=MOD)
		{
			path=retracePath(v,prev);
			path.push_back(v);
		}
		return {dist[v], path};
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
	Int x, y;
	cin >> x >> y;
	RoutePair d = g.fastestPath(x, y);
	if (d.first == MOD)
		logn(-1);
	else
		logn(d.first);
	//debVect(d.second);
	return 0;
}
