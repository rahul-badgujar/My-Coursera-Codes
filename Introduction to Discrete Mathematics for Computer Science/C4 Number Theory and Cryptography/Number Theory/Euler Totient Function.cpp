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

Int etf(Int n)
{
	/*
	Euler Totient Function
	for an Integer n is defined as,
	the count of Integer from [0,n] which are Coprime with n
	Standard Formula = n*(product of 1-1/p)
	for all p, p being prime factor of n
	*/
	/*
	Method used here
	1) Initialize result as n
	2) Consider every number 'p' (where 'p' varies from 2 to ?n). 
	   If p divides n, then do following
		   a) Subtract all multiples of p from 1 to n [all multiples of p
		      will have gcd more than 1 (at least p) with n]
		   b) Update n by repeatedly dividing it by p.
	3) If the reduced n is more than 1, then remove all multiples
	   of n from result.
	*/
	Int ans = n;
	for (Int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			while (n % i == 0)
				n /= i;
			ans -= (ans / i);
		}
	}
	if (n > 1)
		ans -= (ans / n);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(etf(10));

	return 0;
}
