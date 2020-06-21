#include<iostream>
#include<vector>
#define uInt long long unsigned int
#define iList vector<uInt>
#define MX 1e6

using namespace std;

uInt n;
iList dp(MX+1,-1);

uInt fill(uInt i)  {
   if(dp[i]!=-1) return dp[i];
   uInt a1=MX+1,a2=MX+1,a3=MX+1;
   if(3*i<=n)
      a1=fill(3*i)+1;
   if(2*i<=n)
      a2=fill(2*i)+1;
   if((i+1)<=n)
      a3=fill(i+1)+1;
   return min(min(a1,a2),a3);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   
   cin>>n;
   dp[n]=0;
   
   for(uInt i=n;i>=1;i--) {
      dp[i]=fill(i);
   }
   cout<<dp[1]<<endl;
   for(uInt i=1;i<=n;) {
      cout<<i<<' ';
      uInt minInd=i+1;
      uInt possInd[]={i+1,i*2,i*3};
      for(auto x:possInd) {
         if(x<=n) {
            if(dp[x]<=dp[minInd])
               minInd=x;
         }
      }
      i=minInd;
   }
   
   return 0;
}