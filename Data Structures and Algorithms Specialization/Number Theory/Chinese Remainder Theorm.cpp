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

Int getN(const Int &a, const Int &ra, const Int &b, const Int &rb)
{
	/*
	Chinese Remainder Theorm
	for two Intergers a,b such that gcd(a,b)=1
	then for any remainder ra mod a and rb mod b
	there exists an n such that 0<=n<ab (basically n%ab) and
	n mod a=ra and n mod b=rb
	
	Determining n
	1. use Extended Euclids Algorithm for gcd(a,b,x,y)
	2. calculate n=rb*ax+ra*by
	*/
	Int x, y;
	gcd(a, b, x, y);
	Int n = (rb * a * x + ra * b * y) % (a * b);
	if (n < 0)
		n += a * b;
	return n;
}

Int getN(const vector<Int> e, const vector<Int> r)
{
	/*
	Chinese Remainder Theorm for many modules
	Given, array of numbers and their corr remainders e and r resp.
	then, n is sum of
	(r[i]*modInv*factor)%product
	for all 0<=i<len of array
	where,
	product= product of all e[i]
	factor=product/e[i]
	modInv=mod inverse of factor mod e[i] (should be +ve)	 
	*/
	Int product = 1;
	for (auto i : e)
		product *= i;
	Int n = 0;
	for (Int i = 0; i < e.size(); i++)
	{
		Int factor = product / e[i];
		Int modInv, temp;
		gcd(factor, e[i], modInv, temp);
		if (modInv < 0)
			modInv += e[i];
		n += (r[i] * modInv * factor) % product;
	}
	return (n + product) % product;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deb(getN(11, 2, 13, 3));
	deb(getN({3, 4, 5}, {2, 3, 1}));
	return 0;
}
