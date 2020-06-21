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

uInt hashInt(const uInt &x, const uInt m = 100)
{
    uInt p = 10000019;
    uInt a = 385738, b = 294745;
    return ((a * x + b) % p) % m;
}

struct Contact
{
    uInt phone;
    string name;
    Contact()
    {
    }
    Contact(const uInt &p, const string &n)
    {
        phone = p;
        name = n;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    uInt n;
    cin >> n;
    vector<Contact> map[100];
    while (n--)
    {
        string c;
        cin >> c;
        uInt pn;
        cin >> pn;
        uInt pnHash = hashInt(pn);
        if (c == "add")
        {
            string nm;
            cin >> nm;
            bool found = false;
            for (uInt i = 0; i < map[pnHash].size(); i++)
            {
                if (map[pnHash].at(i).phone == pn)
                {
                    map[pnHash].at(i).name = nm;
                    found = true;
                }
            }
            if (!found)
                map[pnHash].push_back(Contact(pn, nm));
        }
        else if (c == "find")
        {
            bool found = false;
            for (uInt i = 0; i < map[pnHash].size(); i++)
            {
                if (map[pnHash].at(i).phone == pn)
                {
                    logn(map[pnHash].at(i).name);
                    found = true;
                }
            }
            if (!found)
                logn("not found");
        }
        else if (c == "del")
        {
            bool found = false;
            uInt i = 0;
            for (i = 0; i < map[pnHash].size(); i++)
            {
                if (map[pnHash].at(i).phone == pn)
                {
                    found = true;
                    break;
                }
            }
            if (found)
                map[pnHash].erase(map[pnHash].begin() + i);
        }
    }
    return 0;
}

/*

LINK :
Status: In Progress

*/