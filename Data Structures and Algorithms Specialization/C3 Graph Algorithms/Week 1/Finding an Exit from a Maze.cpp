#include <iostream>
#include <string>
#include <vector>
#include <cstring>
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

class Graph
{
  public:
	int n;
	vector<vector<int>> adj;
	vector<bool> visited;
	Graph(const int &n)
	{
		this->n = n;
		adj.resize(n + 1);
		for (int i = 1; i <= n; i++)
			adj[i].reserve(n);
		visited.resize(n + 1, false);
	}
	void markEdge(const int &i, const int &j)
	{
		adj[i].push_back(j);
		adj[j].push_back(i);
	}
	bool areConnected(const int &u, const int &v)
	{
		visited[u] = true;
		if (visited[v])
			return true;
		//deb(u);
		//		deb(v);
		bool b = false;
		for (int i = 0; i < adj[u].size() and !b; i++)
		{
			if (!visited[adj[u][i]])
				b = b or areConnected(adj[u][i], v);
		}
		return b;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;
	Graph g(n);
	while (m--)
	{
		int i, j;
		cin >> i >> j;
		g.markEdge(i, j);
	}
	int u, v;
	cin >> u >> v;
	logn(g.areConnected(u, v));
	return 0;
}

/*

LINK :
Status: In Progress

*/