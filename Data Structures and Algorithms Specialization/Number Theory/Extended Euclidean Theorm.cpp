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

// here a <= b
Int gcd(const Int &a, const Int &b, Int &x, Int &y)
{
	/*
	Extended Euclidean
	gcd(a,b) = ax + by
	*/
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	Int x1, y1;
	Int g = gcd(b % a, a, x1, y1);
	y = x1;
	x = y1 - (b / a) * x1;
	return g;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Int a = 30, b = 20, x, y;
	Int hcf = gcd(a, b, x, y);
	deb(hcf);
	deb(x);
	deb(y);

	return 0;
}
