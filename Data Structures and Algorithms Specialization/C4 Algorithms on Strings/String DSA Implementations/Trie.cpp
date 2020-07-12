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
		Int childWords;
		Node(char ch = '$')
		{
			static Int counter = 0;
			id = counter++;
			c = ch;
			childs.resize(Trie::childsSize, nullptr);
			isLeaf = false;
			childWords = 0;
		}
	};
	Node *root;
	static const char base = 'a';
	static const Int childsSize = 26;
	Trie()
	{
		root = new Node();
	}
	void insert(Node *p, const string &s)
	{
		for (auto c : s)
		{
			if (p->childs[c - base] == nullptr)
			{
				p->childs[c - base] = new Node(c);
			}
			p->childWords++;
			p = p->childs[c - base];
		}
		p->isLeaf = true;
		p->childWords++;
	}
	void insert(const string &s)
	{
		insert(root, s);
	}
	Node *remove(Node *p, const string &s, Int i, bool &deleted)
	{
		if (p)
		{
			if (i == s.size())
			{
				if (p->isLeaf)
				{
					p->childWords--;
					p->isLeaf = false;
					if (p->childWords == 0)
					{
						delete p;
						p = nullptr;
					}
					deleted = true;
				}
			}
			else
			{
				p->childs[s[i] - base] = remove(p->childs[s[i] - base], s, i + 1, deleted);
				if (deleted)
				{
					p->childWords--;
					if (p->childWords == 0)
					{
						delete p;
						p = nullptr;
					}
				}
			}
		}
		return p;
	}
	Node *remove(const string &s)
	{
		bool deleted = false;
		root = remove(root, s, 0, deleted);
		return root;
	}
	Int getPrefixCount(Node *p, const string &s)
	{
		Node *curr = p;
		for (Int i = 0; i < s.size(); i++)
		{
			if (curr->childs[s[i] - base] == nullptr)
			{
				return 0;
			}
			curr = curr->childs[s[i] - base];
		}
		return curr->childWords;
	}
	Int getPrefixCount(const string &s)
	{
		return getPrefixCount(root, s);
	}
	bool search(Node *p, const string &s)
	{
		Node *curr = p;
		for (Int i = 0; i < s.size(); i++)
		{
			if (curr->childs[s[i] - base] == nullptr)
			{
				return false;
			}
			curr = curr->childs[s[i] - base];
		}
		if (curr != nullptr and curr->isLeaf)
			return true;
	}
	bool search(const string &s)
	{
		return search(root, s);
	}
	bool isEmpty(Node *p)
	{
		for (Int i = 0; i < childsSize; i++)
		{
			if (p->childs[i] != nullptr)
				return false;
		}
		return true;
	}
	bool isEmpty()
	{
		return isEmpty(root);
	}
	void showContents(Node *p, string &s)
	{
		if (p->isLeaf)
		{
			logn(s);
		}
		for (Int i = 0; i < childsSize; i++)
		{
			if (p->childs[i] != nullptr)
			{
				s += i + base;
				showContents(p->childs[i], s);
			}
		}
		if (!s.empty())
			s.erase(s.length() - 1);
	}
	void showContents()
	{
		string s = "";
		showContents(root, s);
		log('\n');
	}
	void showTrieStructure(Node *p)
	{
		for (Int i = 0; i < 26; i++)
		{
			Node *t = p->childs[i];
			if (t != nullptr)
			{
				cout << p->id << "->" << t->id << ":" << t->c << endl;
				showTrieStructure(t);
			}
		}
	}
	void showTrieStructure()
	{
		showTrieStructure(root);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Trie t;
	string inp[] = {"rahul", "raj", "ra", "bhavesh"};
	Int n = 4;
	for (Int i = 0; i < n; i++)
	{
		t.insert(inp[i]);
	}
	logn(t.root->childWords);
	t.showContents();
	//t.showTrieStructure();
	t.remove(inp[1]);
	t.showContents();
	//t.showTrieStructure();
	logn(t.root->childWords);
	return 0;
}