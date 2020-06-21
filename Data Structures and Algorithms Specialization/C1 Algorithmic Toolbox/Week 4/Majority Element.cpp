#include<iostream>
#include<vector>
#define Int long long

using namespace std;

int main() {
    Int n; cin>>n;
    vector<Int> arr(n,0);
    for(Int i=0;i<n;i++)
        cin>>arr[i];
    Int e=arr[0],c=1;
    for(Int i=1;i<n;i++) {
        if(arr[i]!=e)
            c--;
        else c++;
        if(c<=0) {
            c=1;
            e=arr[i];
        }
    }
    Int count=0;
    for(auto i:arr)
        if(i==e)
            count++;
    if(count>n/2)
        cout<<1;
    else
        cout<<0;
}