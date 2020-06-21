#include<iostream>
#include<vector>
#define list vector<long long int>
typedef long long int Int;
using namespace std;

Int majorElement(list &v,Int a, Int b) {
    Int n=b-a+1;
    if(n==1)
        return v[a];
    else {
        Int i1=majorElement(v,a,a+n/2-1);
        Int i2=majorElement(v,a+n/2,b);
        Int count[2]={0,0};
        for(Int i=a;i<=b;i++) {
            if(v[i]==i1)
                count[0]++;
            else if(v[i]==i2)
                count[1]++;
        }
        if(count[0]>n/2)
            return i1;
        else if(count[1]>n/2)
            return i2;
        else
            return -1;
    }
}

int main() {
    Int n; cin>>n;
    list arr(n,0);
    for(Int i=0;i<n; i++)
        cin>>arr[i];
    Int ans=majorElement(arr,0,n-1);
    if(ans==-1)
        cout<<0;
    else
        cout<<1;
}