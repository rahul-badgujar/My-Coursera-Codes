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
    for(U i=0;i<=n-1;i++)
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

struct Swap
{
    int i,j;
};

vector<Swap> sw;

void shiftdown(vector<int> &arr,int n,int i)
{
    int c1=2*i+1,c2=2*i+2;
    int move=i;
    if(c1<=n-1 and arr[c1]<arr[move])
        move=c1;
    if(c2<=n-1 and arr[c2]<arr[move])
        move=c2;
    if(move!=i)
    {
        Swap s; s.i=i; s.j=move;
        swap(arr[move],arr[i]);
        sw.push_back(s);
        shiftdown(arr,n,move);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin>>n;
    vector<int> arr(n,0);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    for(int i=n/2;i>=0;i--)
    {
        shiftdown(arr,n,i);
    }
    logn(sw.size());
    for(auto s:sw)
    {
        logs(s.i); logs(s.j);
        log('\n');
    }
    return 0;
}

/*

LINK :
Status: In Progress

*/