#include <iostream>
#include <vector>
#define logn(x) cout << x << endl
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define inp(x) cin >> x

using namespace std;

struct Node
{
    long key;
    vector<Node *> childs;

    Node()
    {
        this->key = 0;
    }
    Node(long key)
    {
        this->key = key;
    }
};

long getHeight(Node *t)
{
    if (t == nullptr)
        return 0;
    long m = 0;
    for (long i = 0; i < t->childs.size(); i++)
    {
        m = max(m, getHeight(t->childs[i]));
    }
    return 1 + m;
}

int main()
{
    long n;
    inp(n);
    Node *arr[n];
    long root = 0;
    for (long i = 0; i < n; i++)
    {
        arr[i] = new Node(i);
    }
    for (long i = 0; i < n; i++)
    {
        long t;
        inp(t);
        if (t < 0)
            root = i;
        else
        {
            arr[t]->childs.push_back(arr[i]);
        }
    }
    logn(getHeight(arr[root]));
    for (long i = 0; i < n; i++)
    {
        delete arr[i];
        arr[i] = nullptr;
    }
}