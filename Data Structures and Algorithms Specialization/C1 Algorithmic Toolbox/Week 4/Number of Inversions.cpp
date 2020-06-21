#include <iostream>
#include <vector>
#define list vector<Int>

typedef long long int Int;

using namespace std;

void merge(list &v, Int a, Int b)
{
    Int n = b - a + 1;
    Int a1 = a, b1 = a + n / 2 - 1;
    Int a2 = a + n / 2, b2 = b;
    Int i = a1, j = a2;
    list res;
    while (i <= b1 && j <= b2)
    {
        if (v[i] <= v[j])
        {
            res.push_back(v[i++]);
        }
        else
        {
            res.push_back(v[j++]);
        }
    }
    if (i > b1)
    {
        for (int x = j; x <= b2; x++)
            res.push_back(v[x]);
    }
    else if (j > b2)
    {
        for (int x = i; x <= b1; x++)
            res.push_back(v[x]);
    }
    for (Int i = a; i <= b; i++)
        v[i] = res[i - a];
}

Int countInv(list &v, Int a, Int b)
{
    Int inv = 0;
    Int n = b - a + 1;
    if (n == 1)
        return 0;
    else
    {
        inv += countInv(v, a, a + n / 2 - 1);
        inv += countInv(v, a + n / 2, b);
        Int j = a;
        for (Int i = a + n / 2; i <= b; i++)
        {
            while (v[j] <= v[i] && j <= (a + n / 2 - 1))
            {
                j++;
            }
            if (j >= (a + n / 2))
                break;
            inv += (a + n / 2 - j);
        }
        merge(v, a, b);
        return inv;
    }
}

int main()
{
    Int n;
    cin >> n;
    list arr(n, 0);
    for (Int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << countInv(arr, 0, n - 1);
}