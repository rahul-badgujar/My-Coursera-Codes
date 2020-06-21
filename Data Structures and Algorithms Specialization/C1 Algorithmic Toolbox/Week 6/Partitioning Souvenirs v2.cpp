#include<iostream>
#include<vector>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x
#define inp(x) cin>>x
#define list vector<int>

using namespace std;

bool dp[101][101];
bool visit[101][101];

bool f(int arr[],int n,int ts,list v) {
   if(ts==0) {
      for(int i=0;i<v.size();i++)
         logs(arr[v[i]]);
      return true;
   }
   if(n==0) return false;
   if(visit[n][ts]) return dp[n][ts];
   visit[n][ts]=true;
   if(arr[n-1]>ts)
       dp[n][ts]=f(arr,n-1,ts,v);
   else {
      bool b2=f(arr,n-1,ts,v);
      v.push_back(n-1);
      bool b1=f(arr,n-1,ts-arr[n-1],v);
      dp[n][ts]=b1 or b2;
   }
   return dp[n][ts];
}

int main() {
    int n; cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
       cin>>arr[i];
    int ts=0; cin>>ts;
    list v;
    logn(f(arr,n,ts,v));
    /*for(int i=0;i<=n;i++) {
       for(int j=0;j<=ts;j++) {
          logs(dp[i][j]);
       }
       log("\n");
    }*/
}