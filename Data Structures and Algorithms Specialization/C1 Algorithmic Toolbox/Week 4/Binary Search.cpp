#include<iostream>
#include<vector>
#include<algorithm>
#define Int long long

using namespace std;

Int search(const vector<Int> &v,Int x,Int a, Int b) {
    Int n=b-a+1;
    if(n<=0) return -1;
    Int m=a+n/2;
    if(x==v[m])
        return m;
    else if(x<v[m])
        return search(v,x,a,m-1);
    else if(x>v[m])
        return search(v,x,m+1,b);
   
}

int main() {
    Int n;    cin>>n;
    vector<Int> sarr(n,0);
    for(Int i=0;i<n;i++) 
        cin>>sarr[i];
    Int k;    cin>>k;
    vector<Int> arr(k,0);
    for(Int i=0;i<k;i++)
        cin>>arr[i];
    vector<Int> result(k,0);
    
    for(Int i=0;i<k;i++) {
        result[i]=search(sarr,arr[i],0,n-1);
    }
    for(auto i:result) 
        cout<<i<<' ';
    //vector<Int> a{1,2,3,4,5};
    //cout<<search(a,6,0,4);
}