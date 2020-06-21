#include<iostream>
#include<vector>
#define MW 100000
#define MN 300

typedef long long int Int;

using namespace std;

Int W,n;

Int dpstate[MN+1][MW+1];
bool visited[MN+1][MW+1];
Int weights[MN+1];

Int fill(Int n,Int w) {
  if(n==0 or w==0) return 0;
  if(visited[n][w]) return dpstate[n][w];
  visited[n][w]=true;
  dpstate[n][w]=fill(n-1,w);
  Int v=0;
  if(weights[n-1]<=w) {
     v=fill(n-1,w-weights[n-1])+weights[n-1];
  }
  return max(v,dpstate[n][w]);
}

int main() {
    cin>>W>>n;
    for(Int i=0;i<n;i++)
       cin>>weights[i];
    for(Int i=0;i<=n;i++) {
       for(Int j=0;j<=W;j++) {
          dpstate[i][j]=fill(i,j);
       }
    }
    cout<<dpstate[n][W]<<endl;
}

/*
20 4
18 17 2 4
*/