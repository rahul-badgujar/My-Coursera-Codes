#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#define deb(x) cout << #x << " : " << x << '\n'
#define logn(x) cout << x << '\n'
#define logs(x) cout << x << ' '
#define log(x) cout << x
#define MOD 1000000007
#define uInt unsigned long long int
#define Int int

using namespace std;

typedef vector<Int> ListInt;

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
	ListInt suffArray;
	ListInt firstToLast, lastToFirst;
	ListInt firstOccurance;
	vector<ListInt> rankByRow;
	Int len;
	static const char delim = '$';
	static const char base = 'a';
	static const Int charSetSize = 5;
	SuffixArray(const string &s)
	{
		text = s + delim;
		len = text.length();
		suffArray = buildSuffArray();
		bwt_first = codeBWTfirst();
		bwt_last = codeBWTlast();
		firstOccurance = buildFO();
		firstToLast = buildFTL();
		lastToFirst = buildLTF();
		rankByRow = buildRBR();
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
	ListInt buildSuffArray()
	{
		// Time Complexity O(nLOGn) using Couting Sort
		ListInt order = sortChars();
		ListInt eqvClass = initEqvClass(order);
		Int L = 1;
		while (L < len)
		{
			order = sortDoubled(order, eqvClass, L);
			eqvClass = updateEqvClass(order, eqvClass, L);
			L *= 2;
		}
		return order;
	}
	ListInt sortChars()
	{
		ListInt order(len, 0), count(charSetSize, 0);
		for (Int i = 0; i < len; i++)
			count[index(text[i])]++;
		for (Int i = 1; i < charSetSize; i++)
			count[i] += count[i - 1];
		for (Int i = len - 1; i >= 0; i--)
		{
			Int indx = index(text[i]);
			count[indx]--;
			order[count[indx]] = i;
		}
		return order;
	}
	ListInt initEqvClass(const ListInt &order)
	{
		ListInt eqvClass(len, 0);
		eqvClass[order[0]] = 0;
		for (Int i = 1; i < len; i++)
		{
			Int curr = order[i];
			Int prev = order[i - 1];
			if (text[curr] == text[prev])
				eqvClass[curr] = eqvClass[prev];
			else
				eqvClass[curr] = eqvClass[prev] + 1;
		}
		return eqvClass;
	}
	ListInt sortDoubled(const ListInt &order, const ListInt &eClass, const Int &L)
	{
		ListInt newOrder(len, 0), count(len, 0);
		for (Int i = 0; i < len; i++)
			count[eClass[i]]++;
		for (Int i = 1; i < len; i++)
			count[i] += count[i - 1];
		for (Int i = len - 1; i >= 0; i--)
		{
			Int start = (order[i] - L + len) % len;
			Int cl = eClass[start];
			count[cl]--;
			newOrder[count[cl]] = start;
		}
		return newOrder;
	}
	ListInt updateEqvClass(const ListInt &newOrder, const ListInt &eClass, const Int &L)
	{
		ListInt updClass(len, 0);
		updClass[newOrder[0]] = 0;
		for (Int i = 1; i < len; i++)
		{
			Int curr = newOrder[i], prev = newOrder[i - 1];
			Int midCurr = (curr + L) % len, midPrev = (prev + L) % len;
			if (eClass[curr] == eClass[prev] and eClass[midCurr] == eClass[midPrev])
				updClass[curr] = updClass[prev];
			else
				updClass[curr] = updClass[prev] + 1;
		}
		return updClass;
	}
	vector<ListInt> buildRBR()
	{
		vector<ListInt> rbr;
		rbr.resize(len);
		rbr[0] = ListInt(charSetSize, 0);
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
	ListInt buildFTL()
	{
		ListInt ftl(len, -1);
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
	ListInt buildLTF()
	{
		ListInt ltf(len, -1);
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
	ListInt buildFO()
	{
		// calculate First Occurance in BWT 1st Column
		ListInt fo(charSetSize, -1);
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
	void getOccurances(const string &p, unordered_set<Int> &us)
	{
		Int i = p.length() - 1;
		Int top = 0, bottom = len - 1;
		while (top <= bottom and (top >= 0 and bottom >= 0))
		{
			if (i < 0)
			{
				for (Int i = top; i <= bottom; i++)
					us.insert(suffArray[i]);
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
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> s;
	SuffixArray sa(s);
	Int n;
	cin >> n;
	unordered_set<Int> us;
	while (n--)
	{
		string p;
		cin >> p;
		sa.getOccurances(p, us);
	}
	for (auto i : us)
		logs(i);
	return 0;
}
