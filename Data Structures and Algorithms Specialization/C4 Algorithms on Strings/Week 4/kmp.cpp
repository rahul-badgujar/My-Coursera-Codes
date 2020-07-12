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

class KMP
{
  public:
	string text;
	Int len;
	static const char delim = '$';
	KMP(const string &s)
	{
		text = s;
		len = text.length();
	}
	static vector<Int> buildLCP(const string &s)
	{
		Int n = s.length();
		vector<Int> lcp(n, 0);
		lcp[0] = 0;
		Int border = 0;
		for (Int i = 1; i < n; i++)
		{
			while (border > 0 and s[i] != s[border])
				border = lcp[border - 1];
			if (s[i] == s[border])
				border++;
			else
				border = 0;
			lcp[i] = border;
		}
		return lcp;
	}
	vector<Int> getOccurances(const string &p) const
	{
		Int pLen = p.length();
		string t = p + delim + text;
		Int tLen = t.length();
		vector<Int> lcp = buildLCP(t);
		vector<Int> result;
		for (Int i = pLen + 1; i < tLen; i++)
		{
			if (lcp[i] == pLen)
				result.push_back(i - 2 * pLen);
		}
		return result;
	}
	static vector<Int> getOccurances(const string &p, const string &s)
	{
		Int pLen = p.length();
		string t = p + delim + s;
		Int tLen = t.length();
		vector<Int> lcp = buildLCP(t);
		vector<Int> result;
		for (Int i = pLen + 1; i < tLen; i++)
		{
			if (lcp[i] == pLen)
				result.push_back(i - 2 * pLen);
		}
		return result;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string p,s;
	cin>>p;
	cin>>s;
	debVect(KMP::getOccurances(p, s));

	return 0;
}
