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
Int binoCoeff(const Int &n, const Int &k)
{
	/*
	using standard formula
	C(n,k) = C(n-1,k-1) + C(n-1,k)
	Time : O(n*k)	Space : O(n*k)
	*/
	// Using Bottom Up DP
	Int C[n + 1][k + 1];

	for (Int i = 0; i <= n; i++)
	{
		for (Int j = 0; j <= k; j++)
		{
			if (j == 0 or j == i)
				C[i][j] = 1;
			else
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
	return C[n][k];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(binoCoeff(5, 2));

	return 0;
}
