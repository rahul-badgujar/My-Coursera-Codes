#include<iostream>
#include<deque>
#define logn(x) cout<<x<<endl
#define logs(x) cout<<x<<' '
#define log(x) cout<<x
#define inp(x) cin>>x
#define M 100000

using namespace std;
int arr[M+1];
int n,m;
deque<int> q;

void push(int e)
{
   if(q.empty())
      q.push_back(e);
   else
   {
      while(!q.empty() and arr[q.back()]<=arr[e])
      {
         q.pop_back();
      }
      q.push_back(e);
   }
}

void pop(int i) 
{
   if(q.empty())
      return;
   else 
   {
      while(!q.empty() and q.front()<=i)
         q.pop_front();
   }
}
void printQ(deque<int> t) 
{
   log("deque : ");
   while(!t.empty()) 
   {
      logs(arr[t.front()]);
      t.pop_front();
   }
   log(endl);
}

int main() {
    inp(n);
    for(int i=0;i<n;i++) 
    {   
       inp(arr[i]);
    }
    cin>>m;
    for(int i=0;i<m;i++)
    {
       push(i);
    }
    for(int i=0;i<=n-m;i++) 
    {
       logs(arr[q.front()]);
       //log(endl);
       int j=i+m;
       pop(i);
       push(j);
       //printQ(q);
    }
    
    
}