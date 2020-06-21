#include<iostream>
#include<string>
#define MX 100+1
#define Int long long int

using namespace std;

int n,m;
Int a[MX],b[MX];
int dpState[MX][MX];
bool visited[MX][MX];

int fill(int i,int j) {
   if(visited[i][j]) return dpState[i][j];
   visited[i][j]=true;
   if(i==0 or j==0) return 0;
   
   if(a[i-1]==b[j-1]) 
      return fill(i-1,j-1)+1;
  
   int d1=fill(i,j-1);
   int d2=fill(i-1,j);
   return max(d1,d2);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   
   
   cin>>n;
   for(int i=0;i<n;i++)
      cin>>a[i];
   cin>>m;
   for(int i=0;i<m;i++)
      cin>>b[i];
   
   for(int i=0;i<=n;i++) {
      for(int j=0;j<=m;j++) {
         dpState[i][j]=fill(i,j);
      }
   }
   
   cout<<dpState[n][m];
   
   return 0;
}