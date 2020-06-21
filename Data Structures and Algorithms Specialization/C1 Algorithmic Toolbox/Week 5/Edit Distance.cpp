#include<iostream>
#include<string>
#define MX 100+1

using namespace std;

int n,m;
string a,b;
int dpState[MX][MX];
bool visited[MX][MX];

int fill(int i,int j) {
   if(visited[i][j]) return dpState[i][j];
   visited[i][j]=true;
   if(i==0) return j;
   if(j==0) return i;
  
   int d1=fill(i,j-1)+1;
   int d2=fill(i-1,j)+1;
   int d3=fill(i-1,j-1)+1;
   if(a[i-1]==b[j-1]) d3--;
   return min(min(d1,d2),d3);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   
   
   cin>>a>>b;
   n=a.length();
   m=b.length();
   
   for(int i=0;i<=n;i++) {
      for(int j=0;j<=m;j++) {
         dpState[i][j]=fill(i,j);
      }
   }
   
   cout<<dpState[n][m];
   
   return 0;
}