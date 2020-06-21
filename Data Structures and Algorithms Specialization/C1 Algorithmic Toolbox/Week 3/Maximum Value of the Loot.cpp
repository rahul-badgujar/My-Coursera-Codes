#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define iList vector<Item>

using namespace std;

struct Item {
    double v,w;
    double p;
    Item(double a,double b) {
        v=a; w=b;
        p=v/w;
    }
};

bool compare (Item a,Item b) {
    return a.p > b.p;
}

double solve(iList arr,int n,int c) {
    double ans=0.0;
    int i=0;
    for(auto i:arr) {
        if(c>=i.w) {
            ans+=(i.p*i.w);
            c-=(i.w);
        }
        else {
            ans+=(i.p*c);
            c=0;
        }
    }
    return ans;
}
int main() {
    int n,c; cin>>n>>c;
    iList arr;
    for(int i=0;i<n;i++) {
        int w,v; cin>>v>>w;
        arr.push_back(Item(v,w));
    }
    sort(arr.begin(),arr.end(),compare);
    double ans=solve(arr,n,c);
    cout<<fixed<<setprecision(4)<<ans;
}
