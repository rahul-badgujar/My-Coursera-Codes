#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define MOD 1000000007
#define uInt unsigned long long int
#define Int int

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

class SuffixArray
{
  public:
	string text;
	string bwt_last;
	string bwt_first;
	vector<Int> firstOccurance;
	vector<vector<Int>> rankByRow;
	Int len;
	static const char delim = '$';
	static const char base = 'A';
	static const Int charSetSize = 5;
	SuffixArray(const string &s)
	{
		text = s;
		len = text.length();
	}
	static Int index(const char &c)
	{
		switch (c)
		{
		case delim:
			return 0;
		case 'A':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;
		case 'T':
			return 4;
		}
		return -1;
	}
	static bool strSort(const char &c1, const char &c2)
	{
		return index(c1) < index(c2);
	}
	void buildFO()
	{
		firstOccurance.resize(charSetSize, -1);
		for (Int i = 0; i < len; i++)
		{
			Int ind = index(bwt_first[i]);
			if (firstOccurance[ind] == -1)
				firstOccurance[ind] = i;
		}
	}
	void buildRBR()
	{
		rankByRow.resize(len);
		rankByRow[0] = vector<Int>(charSetSize, 0);
		Int ind = index(bwt_last[0]);
		rankByRow[0][ind]++;
		for (Int i = 1; i < len; i++)
		{
			rankByRow[i] = rankByRow[i - 1];
			ind = index(bwt_last[i]);
			rankByRow[i][ind]++;
		}
	}
	Int getOccurances(const string &p)
	{
		Int i = p.length() - 1;
		Int top = 0, bottom = len - 1;
		vector<Int> occur;
		while (top <= bottom and (top >= 0 and bottom >= 0))
		{
			if (i < 0)
			{
				return bottom - top + 1;
			}
			else
			{
				Int ind = index(p[i--]);
				if (top - 1 >= 0)
					top = firstOccurance[ind] + rankByRow[top - 1][ind];
				else
					top = firstOccurance[ind];
				bottom = firstOccurance[ind] + rankByRow[bottom][ind] - 1;
			}
		}
		return 0;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> s;
	SuffixArray sa(s);
	sa.bwt_last = sa.bwt_first = s;
	sort(sa.bwt_first.begin(), sa.bwt_first.end(), SuffixArray::strSort);
	sa.buildRBR();
	sa.buildFO();
	Int n;
	cin >> n;
	while (n--)
	{
		string p;
		cin >> p;
		logs(sa.getOccurances(p));
	}

	return 0;
}

/*
LINK : 
*/