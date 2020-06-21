#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#define Int long long
#define list vector<Int>
using namespace std;

void partition (list &v, Int a,Int b,Int &x,Int &y) {
    Int r=rand()%(b-a+1)+a;
    Int p=v[r];
    swap(v[a],v[r]);
    Int m=a+1;
    for(Int i=a+1;i<=b;i++) {
        if(v[i]<p) {
            swap(v[i],v[m]);
            m++;
        }
    }
    swap(v[m-1],v[a]);
    Int t=m;
    for(Int i=m;i<=b;i++) {
        if(v[i]==p) {
            swap(v[t],v[i]);
            t++;
        }
    }
    m--;
    x=m; y=m;
    while(v[y]==v[x] && y<=b) y++;
    y--;
}

void qsort(list &v,Int a,Int b) {
    if(a<b) {
        Int m1,m2;
        partition(v,a,b,m1,m2);
        qsort(v,a,m1-1);
        qsort(v,m2+1,b);
    }
}

int main() {
    srand(time(0));
    Int n; cin>>n;
    list arr(n,0);
    for(Int i=0;i<n;i++)
        cin>>arr[i];
    qsort(arr,0,n-1);
    for(auto i:arr)
        cout<<i<<' ';
}