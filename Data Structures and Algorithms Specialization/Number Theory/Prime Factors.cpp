#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
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

vector<Int> getPrimeFactors(Int n)
{
	vector<Int> f;
	// Divide by 2 , Handle Even Nums
	while ((n & 1) == 0)
	{
		n >>= 1;
		f.push_back(2);
	}
	for (Int i = 3; i <= sqrt(n); i += 2)
	{
		while (n % i == 0)
		{
			n /= i;
			f.push_back(i);
		}
	}
	// If n remained in Prime Number
	if (n > 2)
		f.push_back(n);
	return f;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Int n = 315;
	debVect(getPrimeFactors(n));
	return 0;
}
