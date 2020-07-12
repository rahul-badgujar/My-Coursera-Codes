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

class SuffixArray
{
  public:
	struct Suffix
	{
		Int indx, rank1, rank2;
		Suffix()
		{
			indx = rank1 = rank2 = -1;
		}
		static bool compare(const Suffix &s1, const Suffix &s2)
		{
			if (s1.rank1 == s2.rank1)
				return s1.rank2 < s2.rank2;
			else
				return s1.rank1 < s2.rank1;
		}
	};
	string text;
	string bwt_last;
	string bwt_first;
	vector<Int> suffArray;
	vector<Int> firstToLast, lastToFirst;
	vector<Int> firstOccurance;
	vector<vector<Int>> rankByRow;
	Int len;
	static const char delim = '$';
	static const char base = 'a';
	static const Int charSetSize = 27;
	SuffixArray(const string &s)
	{
		text = s + delim;
		len = text.length();
		suffArray = buildSuffArray(text);
		bwt_first = codeBWTfirst();
		bwt_last = codeBWTlast();
		firstOccurance = buildFO();
		firstToLast = buildFTL();
		lastToFirst = buildLTF();
		rankByRow = buildRBR();
	}
	static Int index(const char &c)
	{
		if (c == delim)
			return 0;
		else
			return c - base + 1;
	}
	static bool strSort(const char &c1, const char &c2)
	{
		return index(c1) < index(c2);
	}
	static vector<Int> buildSuffArray(const string &s)
	{
		// Time Complexity : O(N(logN)^2)
		Int n = s.length();
		vector<Int> sa;
		sa.resize(n, -1);
		vector<Suffix> v(n);
		for (Int i = 0; i < n; i++)
		{
			v[i].indx = i;
			v[i].rank1 = index(s[i]);
			if (i + 1 < n)
				v[i].rank2 = index(s[i + 1]);
			else
				v[i].rank2 = -1;
		}
		sort(v.begin(), v.end(), Suffix::compare);
		Int corrIndx[n];
		for (Int k = 4; k < 2 * (n); k *= 2)
		{
			Int rank = 0;
			Int prevR1 = v[0].rank1;
			v[0].rank1 = rank;
			corrIndx[v[0].indx] = 0;
			for (Int i = 1; i < n; i++)
			{
				if (v[i].rank1 == prevR1 and v[i].rank2 == v[i - 1].rank2)
				{
					v[i].rank1 = rank;
				}
				else
				{
					prevR1 = v[i].rank1;
					v[i].rank1 = ++rank;
				}
				corrIndx[v[i].indx] = i;
			}
			for (Int i = 0; i < n; i++)
			{
				Int nextIndx = v[i].indx + k / 2;
				if (nextIndx < n)
					v[i].rank2 = v[corrIndx[nextIndx]].rank1;
				else
					v[i].rank2 = -1;
			}
			sort(v.begin(), v.end(), Suffix::compare);
		}
		for (Int i = 0; i < n; i++)
		{
			sa[i] = v[i].indx;
		}
		return sa;
	}
	vector<vector<Int>> buildRBR()
	{
		vector<vector<Int>> rbr;
		rbr.resize(len);
		rbr[0] = vector<Int>(charSetSize, 0);
		Int ind = index(bwt_last[0]);
		rbr[0][ind]++;
		for (Int i = 1; i < len; i++)
		{
			rbr[i] = rbr[i - 1];
			ind = index(bwt_last[i]);
			rbr[i][ind]++;
		}
		return rbr;
	}
	vector<Int> buildFTL()
	{
		vector<Int> ftl(len, -1);
		unordered_map<char, queue<Int>> m;
		for (Int i = 0; i < len; i++)
		{
			m[bwt_last[i]].push(i);
		}
		for (Int i = 0; i < len; i++)
		{
			queue<Int> &q = m[bwt_first[i]];
			ftl[i] = q.front();
			q.pop();
		}
		return ftl;
	}
	vector<Int> buildLTF()
	{
		vector<Int> ltf(len, -1);
		unordered_map<char, queue<Int>> m;
		for (Int i = 0; i < len; i++)
		{
			m[bwt_first[i]].push(i);
		}
		for (Int i = 0; i < len; i++)
		{
			queue<Int> &q = m[bwt_last[i]];
			ltf[i] = q.front();
			q.pop();
		}
		return ltf;
	}
	vector<Int> buildFO()
	{
		// calculate First Occurance in BWT 1st Column
		vector<Int> fo(charSetSize, -1);
		for (Int i = 0; i < len; i++)
		{
			Int ind = index(bwt_first[i]);
			if (fo[ind] == -1)
				fo[ind] = i;
		}
		return fo;
	}
	// to get Burrows–Wheeler Transform of String
	string codeBWTlast()
	{
		char code[len + 1];
		code[len] = '\0';

		// for bwt_last
		for (Int i = 0; i < len; i++)
		{
			Int ind = suffArray[i] - 1;
			code[i] = text[(ind + len) % len];
		}
		return string(code);
	}
	string codeBWTfirst()
	{
		char code[len + 1];
		code[len] = '\0';

		// for bwt_first
		for (Int i = 0; i < len; i++)
		{
			Int ind = suffArray[i];
			code[i] = text[ind];
		}
		return string(code);
	}
	// to decode Burrows–Wheeler Transform of string
	static string decodeBWT(const string &L)
	{
		Int n = L.length();
		string F = L;
		sort(F.begin(), F.end(), SuffixArray::strSort);
		unordered_map<char, queue<Int>> m;
		for (Int i = 0; i < n; i++)
		{
			m[L[i]].push(i);
		}
		Int ftl[n];
		for (Int i = 0; i < n; i++)
		{
			queue<Int> &q = m[F[i]];
			ftl[i] = q.front();
			q.pop();
		}
		char decode[n + 1];
		decode[n] = '\0';
		Int x = 0;
		for (Int i = 0; i < n; i++)
		{
			x = ftl[x];
			decode[i] = F[x];
		}
		return string(decode);
	}
	vector<Int> getOccurances(const string &p)
	{
		Int i = p.length() - 1;
		Int top = 0, bottom = len - 1;
		vector<Int> occur;
		while (top <= bottom and (top >= 0 and bottom >= 0))
		{
			if (i < 0)
			{
				occur.reserve(bottom - top + 1);
				for (Int i = top; i <= bottom; i++)
					occur.push_back(suffArray[i]);
				break;
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
		return occur;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s = "panamabananas";
	string p = "ana";
	SuffixArray sa(s);
	debVect(sa.getOccurances(p));

	return 0;
}
