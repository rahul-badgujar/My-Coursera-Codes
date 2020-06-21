#include<iostream>
#include<string>
#define MX 100+1
#define Int long long int

using namespace std;

int n,m,p;
Int a[MX],b[MX],c[MX];
int dpState[MX][MX][MX];
bool visited[MX][MX][MX];

int findMax(int arr[],int n) {
   int m=arr[0];
   for(int i=1;i<n;i++)
      m=m<arr[i]?arr[i]:m;
   return m;
}

int fill(int i,int j,int k) {
   if(visited[i][j][k]) return dpState[i][j][k];
   visited[i][j][k]=true;
   if(i==0 or j==0 or k==0) return 0;
   
   if(a[i-1]==b[j-1] && a[i-1]==c[k-1]) 
      return fill(i-1,j-1,k-1)+1;
   int d[3];
   d[0]=fill(i,j,k-1);
   d[1]=fill(i,j-1,k);
   d[2]=fill(i-1,j,k);
   
   return findMax(d,3);
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
   cin>>p;
   for(int i=0;i<p;i++)
      cin>>c[i];
   
   for(int i=0;i<=n;i++) {
      for(int j=0;j<=m;j++) {
         for(int k=0;k<=p;k++)
            dpState[i][j][k]=fill(i,j,k);
      }
   }
   
   cout<<dpState[n][m][p];
   
   return 0;
}