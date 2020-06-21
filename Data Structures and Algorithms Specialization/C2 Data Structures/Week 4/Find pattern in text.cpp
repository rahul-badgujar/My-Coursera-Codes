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

const Int x = 1; //48290174;

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

Int hashString(const string &s, Int i = -1, Int j = -1)
{
    Int n = s.size();
    Int hash = 0;
    if (i == -1)
        i = 0;
    if (j == -1)
        j = n - 1;
    for (Int k = j; k >= i; k--)
        hash = (hash * x + int(s[k])) % MOD;
    return hash % MOD;
}

void precomputeHashes(const string &s, const Int &p, Int A[])
{
    Int y = 1;
    for (Int i = 1; i <= p; i++)
        y = (y * x) % MOD;
    Int n = s.size();
    A[n - p] = hashString(s, n - p, n - 1) % MOD;
    for (Int i = n - p - 1; i >= 0; i--)
    {
        A[i] =
            ((x * A[i + 1]) % MOD + int(s[i]) - (y * int(s[i + p])) % MOD) % MOD;
    }
}

bool areEqual(const string &s, const string &p, const Int &i, const Int &j)
{
    for (Int k = i; k <= j; k++)
    {
        if (p[k - i] != s[k])
            return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string p, s;
    cin >> p >> s;
    Int pSize = p.size(), sSize = s.size();
    Int pHash = hashString(p);
    Int A[sSize - pSize + 1];
    memset(A, 0, sizeof(A));
    precomputeHashes(s, pSize, A);
    // debArr(A, sSize - pSize + 1);
    // deb(pHash);
    for (Int i = 0; i <= sSize - pSize; i++)
    {
        if (A[i] == pHash)
        {
            if (areEqual(s, p, i, i + pSize - 1))
                logs(i);
        }
    }
    return 0;
}

/*

LINK :
Status: In Progress

*/