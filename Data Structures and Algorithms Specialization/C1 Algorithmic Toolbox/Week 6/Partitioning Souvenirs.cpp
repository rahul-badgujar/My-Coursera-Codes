#include<iostream>
#include<unordered_map>
#include<string>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x

using namespace std;

int arr[20];
unordered_map<string,bool> h;

bool allEqZero(int arr[]) {
   if(arr[0]==0 && arr[1]==0 && arr[2]==0)
      return true; 
   return false; 
}
bool solve(int n,int s[]){
   if(allEqZero(s)) return true;
   if(n<=0)  return false;
 
   string k=to_string(n)+","+ 
            to_string(s[0])+","+
            to_string(s[1])+","+
            to_string(s[2]);
   if(h.find(k)==h.end()) {
      bool b=false;
      for(int i=0;i<3 && !b ;i++) {
      int a[]={s[0],s[1],s[2]};
      a[i]-=arr[n-1];
      b=(b or solve(n-1,a));  
      }
      h[k]=b;
   }
   return h[k];
}

int main() {
    int n; cin>>n;
    int sum=0;
    for(int i=0;i<n;i++) {
       cin>>arr[i]; sum+=arr[i];
    }
    if(sum%3==0) {
       int s[]={sum/3,sum/3,sum/3};
       logn(solve(n,s));
    }
    else
       logn(0);
}