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

class DisSet
{
  public:
    vector<int> table, parent, rank;
    int mx = 0;
    DisSet(const int &n)
    {
        table.resize(n + 1);
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> table[i];
            mx = max(mx, table[i]);
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
    void munion(const int &x, const int &y)
    {
        int xid = find(x);
        int yid = find(y);
        if (xid != yid)
        {
            if (rank[xid] < rank[yid])
            {
                parent[xid] = yid;
                table[yid] += table[xid];
                mx = max(mx, table[yid]);
                table[xid] = 0;
            }
            else if (rank[xid] > rank[yid])
            {
                parent[yid] = xid;
                table[xid] += table[yid];
                mx = max(mx, table[xid]);
                table[yid] = 0;
            }
            else
            {
                parent[xid] = yid;
                table[yid] += table[xid];
                mx = max(mx, table[yid]);
                table[xid] = 0;
                rank[yid]++;
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    DisSet s(n);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        s.munion(a, b);
        logn(s.mx);
    }

    return 0;
}

/*

LINK :
Status: In Progress

*/