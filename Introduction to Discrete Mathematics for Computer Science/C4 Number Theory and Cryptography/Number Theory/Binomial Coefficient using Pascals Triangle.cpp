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
	vector<Int> C(k + 1, 0);
	C[0] = 1; // First Row of Pascals Triangle
	// For next Rows
	for (Int i = 1; i <= n; i++)
	{
		// Calc next row from previous
		for (Int j = min(i, k); j > 0; j--)
		{
			C[j] += C[j - 1];
		}
	}
	return C[k];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(binoCoeff(5, 2));

	return 0;
}
