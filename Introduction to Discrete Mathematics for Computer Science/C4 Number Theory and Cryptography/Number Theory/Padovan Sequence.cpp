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

Int padovan(const Int &n)
{
	/*
	Padovan Sequence
	P(n) = P(n-2) + P(n-3);
	and P(0)=P(1)=P(2)=1;
	
	Use in Sprial of Equilateral Triangles
	*/
	Int seq[3] = {1, 1, 1};
	for (Int i = 3; i <= n; i++)
	{
		Int t = seq[1] + seq[0];
		seq[0] = seq[1];
		seq[1] = seq[2];
		seq[2] = t;
	}
	return seq[2];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (Int i = 0; i < 10; i++)
	{
		logs(padovan(i));
	}

	return 0;
}
