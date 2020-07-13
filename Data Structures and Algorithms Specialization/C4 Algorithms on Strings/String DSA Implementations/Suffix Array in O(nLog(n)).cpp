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
	string text;
	Int len;
	ListInt suffArray;
	static const char delim = '$';
	static const char base = 'a';
	static const Int charSetSize = 27;
	SuffixArray(const string &s)
	{
		text = s + delim;
		len = text.length();
		suffArray = buildSuffArray();
	}
	static Int index(const char &c)
	{
		if (c == delim)
			return 0;
		else
			return c - base + 1;
	}
	ListInt buildSuffArray()
	{
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
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s = "panamabananas";
	SuffixArray sa(s);
	debVect(sa.suffArray);

	return 0;
}
