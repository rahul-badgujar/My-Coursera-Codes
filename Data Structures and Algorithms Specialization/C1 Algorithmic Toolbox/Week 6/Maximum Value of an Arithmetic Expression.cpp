#include<iostream>
#include<string>
#include<climits>
#include<stdio.h>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x
#define inp(x) cin>>x
#define MX 29

using namespace std;

typedef long long int Int;

Int minVal(string,Int,Int);
Int maxVal(string,Int,Int);

Int dpMax[MX+1][MX+1];
Int dpMin[MX+1][MX+1];

Int operate(Int a,Int b,char o) {
   switch(o) {
      case '+': return a+b;
      case '-': return a-b;
      case '*': return a*b;
      default : logn("Error");
   }
}

Int minVal(string exp,Int i,Int j) {
   if(i==j)
      return exp[i]-Int('0');
   if(dpMin[i][j]==-1) {
      Int mn=LLONG_MAX;
      for(Int k=i;k<=j-2;k+=2) {
         Int mx1=maxVal(exp,i,k);
         Int mx2=maxVal(exp,k+2,j);
         Int mn1=minVal(exp,i,k);
         Int mn2=minVal(exp,k+2,j);
         mn=min(mn,operate(mx1,mx2,exp[k+1]));
         mn=min(mn,operate(mn1,mn2,exp[k+1]));
         mn=min(mn,operate(mx1,mn2,exp[k+1]));
         mn=min(mn,operate(mn1,mx2,exp[k+1]));
      }
      dpMin[i][j]=mn;
   }
   return dpMin[i][j];
}

Int maxVal(string exp,Int i,Int j) {
   if(i==j)
      return exp[i]-Int('0');
   if(dpMax[i][j]==-1) {
      Int mx=LLONG_MIN;
      for(Int k=i;k<=j-2;k+=2) {
         Int mx1=maxVal(exp,i,k);
         Int mx2=maxVal(exp,k+2,j);
         Int mn1=minVal(exp,i,k);
         Int mn2=minVal(exp,k+2,j);
         mx=max(mx,operate(mx1,mx2,exp[k+1]));
         mx=max(mx,operate(mn1,mn2,exp[k+1]));
         mx=max(mx,operate(mx1,mn2,exp[k+1]));
         mx=max(mx,operate(mn1,mx2,exp[k+1]));
      }
      dpMax[i][j]=mx;
   }
   return dpMax[i][j];
}

int main() {
    //memset(dpMax,-1,sizeof(dpMax));
   // memset(dpMin,-1,sizeof(dpMin));
    for(Int i=0;i<=MX;i++) {
       for(Int j=0;j<=MX;j++) {
          dpMax[i][j]=-1;
          dpMin[i][j]=-1;
       }
    }
    string exp; cin>>exp;
    Int n=exp.length();
    logn(maxVal(exp,0,n-1));
}