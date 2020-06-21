#include<iostream>
#include<vector>
#include<string>
#define Int long long int

using namespace std;

struct Path {
    char id;
    Int x,y;
    bool active;
    
    Path(char c, Int a, Int b) {
        id=c; x=a; y=b;
        active=false;
    }
};

int main() {
    Int n,m=0; cin>>n;
    vector<Path> paths;
    int id=1;
    for(Int i=0;i<n;i++) {
        Int a,b; cin>>a>>b;
        paths.push_back(id++,a,b);
        m=b>m?b:m;
    }
    string line(m+1,"");
    int visited=0, visits=0;
    while(visited<n) {
        
    }
}