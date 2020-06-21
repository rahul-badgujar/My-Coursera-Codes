#include<iostream>
#include<stack>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x
#define inp(x) cin>>x

using namespace std;

int main() {
    long q; cin>>q;
    stack<long> st;
    stack<long> m;
    while(q--)
    {
       string op; cin>>op;
       if(op=="max") 
       {
          logn(m.top());
       }
       else 
       {
          if(op=="push") 
          {
             long v; cin>>v;
             if(m.empty()) 
             {
                st.push(v);
                m.push(v);
             }
             else
             {
                st.push(v);
                if(m.top()<=v)
                   m.push(v);
             }
          }
          else if(op=="pop")
          {
             long v=st.top();
             st.pop();
             if(v==m.top())
                m.pop();
          }
       }
    }
}