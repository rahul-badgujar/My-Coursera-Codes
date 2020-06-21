#include <iostream>
#include <string>
#include <vector>
#include <queue>
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

class Processor
{
  public:
    Int id, jt;
    Processor(Int i, Int j)
    {
        this->id = i;
        this->jt = j;
    }
};

bool operator<(const Processor &p1, const Processor &p2)
{
    if (p1.jt == p2.jt)
        return p1.id > p2.id;
    else
        return p1.jt > p2.jt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<Processor> pq;

    Int m, n;
    cin >> m >> n;
    for (Int i = 0; i < m; i++)
        pq.push(Processor(i, 0));
    for (Int i = 0; i < n; i++)
    {
        Int x;
        cin >> x;
        Processor t = pq.top();
        pq.pop();
        logs(t.id);
        logn(t.jt);
        t.jt += x;
        pq.push(t);
    }

    return 0;
}

/*

LINK : 
Status: Accepted

*/