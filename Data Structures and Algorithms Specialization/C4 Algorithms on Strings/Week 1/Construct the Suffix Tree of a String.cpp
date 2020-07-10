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

class SuffixTree
{
  public:
	struct Node
	{
		Int l, r;
		Int init;
		vector<Node *> childs;
		static const Int childsSize = 5;
		static const char base = 'a';
		Node(Int a = -1, Int b = -1, Int i = -1)
		{
			l = a;
			r = b;
			init = i;
			childs.resize(childsSize, nullptr);
		}
	};
	string text;
	Int len;
	Node *root;
	SuffixTree(const string &s)
	{
		text = s;
		len = s.length();
		root = new Node();
		buildSuffixTree();
	}
	void buildSuffixTree()
	{
		for (Int i = 0; i < len; i++)
		{
			insert(i);
		}
	}
	void insert(Int i)
	{
		Node *p = root;
		Int init = i;
		while (i < len)
		{
			if (p->childs[index(text[i])] == nullptr)
			{
				p->childs[index(text[i])] = new Node(i, len - 1, init);
				return;
			}
			Node *t = p->childs[index(text[i])];
			Int j, save = i;
			for (j = t->l; j <= t->r; j++, i++)
			{
				if (text[i] != text[j])
					break;
			}
			if (j > t->r)
			{
				p = t;
			}
			else
			{
				Node *n = new Node(t->l, j - 1);
				t->l = j;
				n->childs[index(text[j])] = t;
				p->childs[index(text[save])] = n;
				p = n;
			}
		}
	}
	static Int index(const char &c)
	{
		switch (c)
		{
		case 'A':
			return 0;
		case 'T':
			return 1;
		case 'G':
			return 2;
		case 'C':
			return 3;
		case '$':
			return 4;
		}
		return -1;
	}
	void showContents(Node *p)
	{
		if (p != root)
		{
			logn(text.substr(p->l, p->r - p->l + 1));
		}
		for (Int i = 0; i < Node::childsSize; i++)
		{
			Node *t = p->childs[i];
			if (t != nullptr)
			{
				showContents(t);
			}
		}
	}
	void showContents()
	{
		showContents(root);
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> s;
	SuffixTree t(s);
	t.showContents();
	return 0;
}