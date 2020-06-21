#include<iostream>
#include<vector>

using namespace std;

int main() {
    int d,m,n; cin>>d>>m>>n;
    vector<int> arr(n,0);
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }
    int ans=0;
    int nxt=m;
    for(int i=0;i<n;i++) {
        if(arr[i]>nxt)  {
            if(i==0 || (arr[i]-arr[i-1])>m) {
                ans=-1; break;
            }
            else {
                nxt=arr[i-1]+m;
                i--; ans++;
            }
        }
     }
     if(nxt<d && ans!=-1) {
         nxt=arr[n-1]+m;
         if(nxt<d) ans=-1;
         else ans++;
     }
     cout<<ans;
}