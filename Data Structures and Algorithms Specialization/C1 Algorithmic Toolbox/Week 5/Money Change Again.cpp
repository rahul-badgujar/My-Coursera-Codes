#include<iostream>
#include<vector>
#include<string>
#define uInt long long unsigned int
#define Int long long int
#define iList vector<Int>
#define log(x) cout<<x
#define logn(x) cout<<x<<'\n';
#define logs(x) cout<<x<<' ';
#define inp(x) cin>>x
#define M 1001

using namespace std; 

int domin[]={1,3,4};
iList dp(M,-1);

Int fill(Int n) {
   if(n==0) return 0;
   if(dp[n]!=-1) return dp[n];
   Int mn=M+1;
   for(auto i:domin) {
      if(n-i>=0) {
         Int c=fill(n-i)+1;
         if(c<mn)
            mn=c;
      }
   }
   return mn;
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   dp[0]=0;
   Int n; cin>>n;
   for(Int i=1;i<=n;i++) {
      dp[i]=fill(i);
   }
   logn(dp[n]);
   return 0;
}