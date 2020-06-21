#include<iostream>
#include<vector>
#define Int long long unsigned int

using namespace std;

int main() {
    Int n; cin>>n;
    vector<Int> arr;
    Int x=1;
    while(n>0) {
        if(n<x) {
            arr[arr.size()-1]+=n;
            n=0;
        }
        else {
            arr.push_back(x);
            n-=x;
        }
        x++;
    }
    cout<<arr.size()<<endl;
    for(auto i: arr) 
        cout<<i<<' ';
}