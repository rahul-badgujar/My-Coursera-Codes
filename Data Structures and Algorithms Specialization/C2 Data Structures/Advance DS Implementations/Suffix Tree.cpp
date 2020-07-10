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
		static const Int childsSize = 27;
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
			//deb(i);
			insert(i);
			//log('\n');
		}
	}
	void insert(Int i)
	{
		Node *p = root;
		Int init = i;
		while (i < len)
		{
			Int ind = index(text[i]);
			if (p->childs[ind] == nullptr)
			{
				p->childs[ind] = new Node(i, len - 1, init);
				return;
			}
			Node *t = p->childs[ind];
			Int j;
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
				p->childs[ind] = n;
				p = n;
			}
		}
	}
	static Int index(const char &c)
	{
		if (c == '$')
			return Node::childsSize - 1;
		else
			return c - Node::base;
	}
	void showContents(Node *p, string &s)
	{
		if (p->init != -1)
		{
			logs(s);
			logn(p->init);
		}
		for (Int i = 0; i < Node::childsSize; i++)
		{
			Node *t = p->childs[i];
			if (t != nullptr)
			{
				string temp = s;
				s += text.substr(t->l, t->r - t->l + 1);
				showContents(t, s);
				s = temp;
			}
		}
	}
	void showContents()
	{
		string s("");
		showContents(root, s);
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