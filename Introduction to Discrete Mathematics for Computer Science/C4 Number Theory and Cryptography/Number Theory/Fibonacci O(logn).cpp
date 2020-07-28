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

void multiplyMat(Int F[2][2], Int M[2][2])
{
	int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
	int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
	int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
	int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}

void power(Int F[2][2], const Int &n)
{
	if (n <= 1)
		return;
	power(F, n / 2);
	multiplyMat(F, F);
	if (n & 1)
	{
		Int M[2][2] = {{1, 1}, {1, 0}};
		multiplyMat(F, M);
	}
}

Int fib(const Int &n)
{
	/*
	Matrix Multiplication Method O(logn)
	Fibonacci of N, where N>0 =
	Matrix [[1,1],[1,0]] power to N-1	
	*/
	if (n <= 0)
		return 0;
	Int F[2][2] = {{1, 1}, {1, 0}};
	power(F, n - 1);
	return F[0][0];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (Int i = 0; i < 10; i++)
	{
		logs(fib(i));
	}

	return 0;
}
