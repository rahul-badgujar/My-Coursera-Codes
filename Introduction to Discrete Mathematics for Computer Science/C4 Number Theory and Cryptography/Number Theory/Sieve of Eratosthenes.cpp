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

vector<Int> primesTill(const Int &n)
{
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for (Int i = 2; i * i <= n; i++)
	{
		if (isPrime[i])
		{
			for (Int j = i * i; j <= n; j += i)
				isPrime[j] = false;
		}
	}
	vector<Int> primes;
	for (Int i = 2; i <= n; i++)
	{
		if (isPrime[i])
			primes.push_back(i);
	}
	return primes;
}

vector<Int> primesInRange(const Int &l, const Int &r)
{
	vector<bool> isPrime(r - l + 1, true);
	for (Int i = 2; i * i <= r; i++)
	{
		for (Int j = max(i * i, (l + (i - 1)) / i * i); j <= r; j += i)
			isPrime[j - l] = false;
	}
	vector<Int> primes;
	for (Int i = max(2LL, l); i <= r; i++)
	{
		if (isPrime[i - l])
			primes.push_back(i);
	}
	return primes;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	debVect(primesTill(100));
	debVect(primesInRange(10, 30));

	return 0;
}
