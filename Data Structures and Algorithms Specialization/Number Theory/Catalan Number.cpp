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

// Binomial Coefficient is C(n,k)
// It is coef of X^k in (1+X)^n
Int binoCoeff(Int n, Int k)
{
	/*
	using Combination Formula O(n)
	C(n,k) = n!/(k!(n-k)!) = C(n,n-k) = n!/((n-k)!*k!)
	C(n,k) = [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1] 
	*/
	Int coe = 1;
	k = min(k, n - k);
	for (Int i = 0; i < k; i++)
	{
		coe *= (n - i);
		coe /= (i + 1);
	}
	return coe;
}

Int catalan(const Int &n)
{
	/*
	using formula O(n)
	Cat(n) = C(2n,n)/n+1
	*/
	Int c=binoCoeff(2*n,n);
	return c/(n+1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for(Int i=0;i<10;i++)
	{
		deb(catalan(i));
	}

	return 0;
}
