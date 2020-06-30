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

class UFDS
{
  public:
	vector<int> parent, rank;
	UFDS(const int &n)
	{
		parent.resize(n);
		rank.resize(n);
		for (int i = 0; i <= n - 1; i++)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}
	int find(const int &x)
	{
		if (x != parent[x])
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	void unite(const int &x, const int &y)
	{
		int xid = find(x);
		int yid = find(y);
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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	return 0;
}

/*

LINK :
Status: In Progress

*/