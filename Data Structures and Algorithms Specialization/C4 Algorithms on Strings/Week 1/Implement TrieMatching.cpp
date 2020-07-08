#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
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

class Trie
{
  public:
	struct Node
	{
		Int id;
		char c;
		bool isLeaf;
		vector<Node *> childs;
		Node(Int i = -1, char ch = '$')
		{
			id = i;
			c = ch;
			childs.resize(26, nullptr);
			isLeaf = false;
		}
	};
	Node *root;
	Trie()
	{
		root = new Node(0);
	}
	void insert(const string &s)
	{
		static Int clock = 0;
		Node *curr = root;
		for (auto c : s)
		{
			if (curr->childs[c - 'A'] == nullptr)
			{
				curr->childs[c - 'A'] = new Node(++clock, c);
			}
			curr = curr->childs[c - 'A'];
		}
		curr->isLeaf = true;
	}
	void matchInText(const string &t)
	{
		vector<Int> ind;
		for (Int i = 0; i < t.size(); i++)
		{
			Int j = i;
			Node *curr = root;
			while (curr->childs[t[j] - 'A'] != nullptr and j < t.size())
			{
				curr = curr->childs[t[j] - 'A'];
				j++;
			}
			if (curr != nullptr and curr->isLeaf)
			{
				ind.push_back(i);
			}
		}
		sort(ind.begin(), ind.end());
		debVect(ind);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Trie t;
	string txt;
	cin >> txt;
	Int n;
	cin >> n;
	while (n--)
	{
		string s;
		cin >> s;
		t.insert(s);
	}
	t.matchInText(txt);
	return 0;
}

/*
LINK : 
*/