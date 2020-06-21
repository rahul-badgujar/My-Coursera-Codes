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

Int hashString(const string &s)
{
    Int n = s.size();
    Int hash = 0, x = 263;
    for (Int i = n - 1; i >= 0; i--)
        hash = (hash * x + int(s[i])) % MOD;
    return hash;
}

class Map
{
  public:
    Int m;
    vector<vector<string>> map;
    Map(const Int &m)
    {
        this->m = m;
        map.resize(m);
    }
    bool find(const string &s)
    {
        Int hash = hashString(s) % m;
        for (Int i = 0; i < map[hash].size(); i++)
            if (map[hash][i] == s)
                return true;
        return false;
    }
    void add(const string &s)
    {
        if (!find(s))
        {
            Int hash = hashString(s) % m;
            map[hash].push_back(s);
        }
    }
    void check(const Int &x)
    {
        for (Int i = map[x].size() - 1; i >= 0; i--)
        {
            logs(map[x][i]);
        }
        log('\n');
    }
    void del(const string &s)
    {
        Int hash = hashString(s) % m;
        bool found = false;
        vector<string> &v = map[hash];
        Int i = 0;
        for (i = 0; i < v.size(); i++)
            if (v[i] == s)
            {
                found = true;
                break;
            }
        if (found)
            v.erase(v.begin() + i);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Int m, n;
    cin >> m >> n;
    Map mp(m);
    while (n--)
    {
        string c;
        cin >> c;
        if (c == "add")
        {
            string s;
            cin >> s;
            mp.add(s);
        }
        else if (c == "check")
        {
            Int i;
            cin >> i;
            mp.check(i);
        }
        else if (c == "find")
        {
            string s;
            cin >> s;
            if (mp.find(s))
                logn("yes");
            else
                logn("no");
        }
        else if (c == "del")
        {
            string s;
            cin >> s;
            mp.del(s);
        }
    }
    return 0;
}

/*

LINK :
Status: In Progress

*/