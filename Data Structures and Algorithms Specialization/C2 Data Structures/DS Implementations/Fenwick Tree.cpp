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

// Range Sum Query
class BIT
{
  public:
	vector<Int> arr, tree;
	Int n;
	BIT(const vector<Int> &v)
	{
		n = v.size();
		// Use 1 Based Indexing in BIT
		arr.resize(n + 1, 0);
		tree.resize(n + 1, 0);
		for (Int i = 1; i <= n; i++)
		{
			arr[i] = v[i - 1];
			update(i - 1, v[i - 1]);
		}
	}
	void update(Int i, const Int &val)
	{
		i++; // 1 Based Indexing
		while (i <= n)
		{
			tree[i] += val;
			i += (i & -i);
		}
	}
	Int query(Int i)
	{
		i++; // 1 Based Indexing
		Int result = 0;
		while (i > 0)
		{
			result += tree[i];
			i -= (i & -i);
		}
		return result;
	}
	Int query(const Int &i, const Int &j)
	{
		return (query(j) - query(i - 1));
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<Int> v({1, 3, 5, 7, 9, 10});
	BIT b(v);
	debVect(v);
	Int q = 10;
	while (q--)
	{
		Int i, j;
		cin >> i >> j;
		logn(b.query(i, j));
	}

	return 0;
}
