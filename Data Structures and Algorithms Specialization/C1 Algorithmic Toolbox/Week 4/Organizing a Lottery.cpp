#include<iostream>
#include<vector>
#define Int long long
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define M 100000000

using namespace std;

struct Segment {
   Int x,y;
   Segment (Int a,Int b) {
      x=a; y=b;
   }
};

int main() {
    Int s,p; cin>>s>>p;
    vector<Segment> seg;
    Int mx=-M,mn=M;
    for(Int i=0;i<s;i++) {
       Int a,b; cin>>a>>b;
       seg.push_back(Segment(a,b));
       if(a<mn) mn=a;
       if(b>mx) mx=b;
    }
    vector<Int> points(p,0);
    for(Int i=0;i<p;i++)
       cin>>points[i];
    vector<Int> line(mx-mn+1,0);
    for(auto i:seg) {
       for(Int t=i.x-mn;t<=i.y-mn;t++) {
          line[t]++;
       }
    }
    for(auto i:points) {
       if(i>=mn && i<=mx)
          logs(line[i-mn]);
       else
          logs(0);
    }
}