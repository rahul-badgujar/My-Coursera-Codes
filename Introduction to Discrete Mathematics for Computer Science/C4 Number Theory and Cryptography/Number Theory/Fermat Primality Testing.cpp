#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
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

Int gcd(const Int &a, const Int &b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

Int modExp(Int x, Int n, const Int &M)
{
	Int result = 1;
	while (n > 0)
	{
		if ((n & 1) == 1)
		{
			result = ((result % M + M) * (x % M + M) + M) % M;
		}
		x = ((x % M + M) * (x % M + M) + M) % M;
		n >>= 1;
	}
	return (result % M + M) % M;
}

bool isPrime(const Int &n)
{
	if (n < 4)
		return (n == 3 or n == 2);
	/*
	Fermat Primality Testing for probabilistic Primality Test
	returns TRUE for Prime Number, returns TRUE/FALSE for Composite
	
	For a Prime number p, 
	and any number a (1 < a < p)
	then (a^(p-1))%p == 1
	*/
	// High value of k, means high accuracy
	Int k = 3;
	while (k--)
	{
		Int a = rand() % (n - 3) + 2; // Range [2,n-2]
		if (gcd(n, a) != 1)
			return false;
		if (modExp(a, n - 1, n) != 1)
			return false;
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(isPrime(23));
	deb(isPrime(14));

	return 0;
}
