#include<iostream>
#include<vector>
#include<deque>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x
#define inp(x) cin>>x

typedef long long int Int;

struct Task 
{
   Int st,pt;
   Int ft;
   Task(Int s,Int p) 
   {
      st=s; pt=p;
      ft=s+p;
   }
};

using namespace std;

int main() {
    deque<Task> q;
    Int s,n; cin>>s>>n;
    for(Int i=0;i<n;i++)
    {
       Int si,pi; cin>>si>>pi;
       if(q.empty())
       {
          if(s>0) 
          {
             Task t(si,pi);
             logn(t.st);
             q.push_back(t);
          }
          else
          {
             logn(-1);
             continue;
          }
       }
       else
       {
          while(q.front().ft<=si)
          {
                q.pop_front();
                if(q.empty())
                   break;
          }
          if(q.empty() && s>0) 
          {
             Task t(si,pi);
             logn(t.st);
             q.push_back(t);
          }
          else if(q.size()<s) 
          {
             Int f=q.back().ft;
             if(f>si)
                si=f;
             Task t(si,pi);
             logn(t.st);
             q.push_back(t);
          }
          else
          {
             logn(-1);
             continue;
          }
       }
    }
}