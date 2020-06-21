#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

bool compare(string a, string b) {
    string x=a+b, y=b+a;
    return x>y;
}
int main() {
    int n; cin>>n;
    vector<string> arr;
    for(int i=0;i<n;i++) {
        string t;
        cin>>t;
        arr.push_back(t);
    }
    sort(arr.begin(),arr.end(),compare);
    for(auto i:arr)
        cout<<i;
}