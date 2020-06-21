#include <iostream>
#include <string>
#include <stack>
#define logn(x) cout << x << endl
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define inp(x) cin >> x

using namespace std;

bool isOBracket(char c)
{
    switch (c)
    {
    case '(':
    case '[':
    case '{':
        return true;
    default:
        return false;
    }
}

bool isCBracket(char c)
{
    switch (c)
    {
    case ')':
    case ']':
    case '}':
        return true;
    default:
        return false;
    }
}

bool match(char c1, char c2)
{
    switch (c1)
    {
    case '(':
        return c2 == ')';
    case '[':
        return c2 == ']';
    case '{':
        return c2 == '}';
    default:
        return false;
    }
}

int main()
{
    string s;
    getline(cin,s);
    stack<long long int> st;
    long long int i;
    for (i = 0; i < s.length(); i++)
    {
        if (isOBracket(s[i]))
        {
            st.push(i);
        }
        else if (isCBracket(s[i]))
        {
            char t;
            if (st.empty())
            {
                st.push(i);
                break;
            }
            else
                t = st.top();
            if (match(s[t], s[i]))
            {
                st.pop();
            }
            else
            {
                st.push(i);
                break;
            }
        }
    }
    if (st.empty())
    {
        logn("Success");
    }
    else
        logn(st.top() + 1);
}