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

Int gcd(const Int &a, const Int &b, Int &x, Int &y)
{
	/*
	Extended Euclidean
	gcd(a,b) = ax + by
	*/
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	Int x1, y1;
	Int g = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

Int modInverse(const Int &a, const Int &b)
{
	/*
	Multiplicative Module Inverse of A under M is B such that
	(A*B)%M=1 === A*B=1(%M)
	
	Method used:
	Extended Euclidean Coefficient
	gcd(A,B)=A*x+B*y
	Here
	x=MMI of A under B
	y=MMI of B under A
	*/
	Int x, y;
	gcd(a, b, x, y);
	return x;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(modInverse(16, 10));

	return 0;
}
