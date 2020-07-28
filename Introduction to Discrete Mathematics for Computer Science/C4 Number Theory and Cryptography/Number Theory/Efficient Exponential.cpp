#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define MOD 1000000007
#define uInt unsigned long long int
#define Int long long int

using namespace std;

template <typename T, typename U>
void debArr(T arr[], U n)
{
	for (U i = 0; i <= n - 1; i++)
	{
		logs(arr[i]);
	}
	log(endl);
}

template <typename T>
void debVect(vector<T> arr)
{
	for (auto i : arr)
	{
		logs(i);
	}
	log(endl);
}

Int exp(Int x, Int n)
{
	Int result = 1;
	while (n >= 1)
	{
		if ((n & 1) == 1)
		{
			result = result * x;
		}
		x = x * x;
		n >>= 1;
	}
	return result;
}

Int exp(Int x, Int n, const Int m)
{
	Int result = 1;
	x = x % m;
	if (x > 0 and abs(x - m) < abs(x))
	{
		x = x - m;
	}
	else if (x < 0 and abs(x + m) < abs(x))
	{
		x = x + m;
	}
	n = n % (m - 1); // using Fermants Little Theorm
	while (n >= 1)
	{
		if ((n & 1) == 1)
		{
			result = (result * x) % m;
		}
		x = (x * x) % m;
		n >>= 1;
	}
	return (result + m) % m;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(exp(6, 3));
	deb(exp(6, 3, 10));

	return 0;
}
