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

class BST
{
  public:
	struct Node
	{
		Int key;
		Node *left, *right, *parent;
		Int size;
		Node(const Int &k) : key(k), size(1)
		{
			left = right = parent = nullptr;
		}
		~Node()
		{
			key = 0;
			size = 0;
			left = right = parent = nullptr;
		}
	};
	Node *root;
	BST() : root(nullptr)
	{
	}
	Node *find(Node *par, const Int &k)
	{
		if (par)
		{
			if (par->key == k)
			{
				return par;
			}
			else if (par->key < k)
			{
				if (par->right == nullptr)
					return par;
				else
					return find(par->right, k);
			}
			else if (par->key > k)
			{
				if (par->left == nullptr)
					return par;
				else
					return find(par->left, k);
			}
		}
		return nullptr;
	}
	Node *find(const Int &k)
	{
		return find(root, k);
	}
	Node *insert(Node *par, const Int &k)
	{
		if (par == nullptr)
		{
			return new Node(k);
		}
		if (k < par->key)
		{
			par->left = insert(par->left, k);
			par->left->parent = par;
		}
		else if (k > par->key)
		{
			par->right = insert(par->right, k);
			par->right->parent = par;
		}
		adjustSize(par);
		return par;
	}
	Node *insert(const Int &k)
	{
		root = insert(root, k);
		adjustSize(root);
		return root;
	}
	vector<Int> getInorder(Node *par)
	{
		vector<Int> elem;
		if (par)
		{
			vector<Int> L = getInorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			elem.push_back(par->key);
			vector<Int> R = getInorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
		}
		return elem;
	}
	vector<Int> getInorder()
	{
		return getInorder(root);
	}
	vector<Int> getPreorder(Node *par)
	{
		vector<Int> elem;
		if (par)
		{
			elem.push_back(par->key);
			vector<Int> L = getPreorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			vector<Int> R = getPreorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
		}
		return elem;
	}
	vector<Int> getPreorder()
	{
		return getPreorder(root);
	}
	vector<Int> getPostorder(Node *par)
	{
		vector<Int> elem;
		if (par)
		{
			vector<Int> L = getPostorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			vector<Int> R = getPostorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
			elem.push_back(par->key);
		}
		return elem;
	}
	vector<Int> getPostorder()
	{
		return getPostorder(root);
	}
	Node *leftDescendant(Node *n)
	{
		if (n)
		{
			if (n->left == nullptr)
				return n;
			else
				return leftDescendant(n->left);
		}
		return nullptr;
	}
	Node *rightDescendant(Node *n)
	{
		if (n)
		{
			if (n->right == nullptr)
				return n;
			else
				return rightDescendant(n->right);
		}
		return nullptr;
	}
	Node *leftAncestor(Node *n)
	{
		if (n->parent)
		{
			if (n->parent->key < n->key)
				return n->parent;
			else
				return leftAncestor(n->parent);
		}
		return nullptr;
	}
	Node *rightAncestor(Node *n)
	{
		if (n->parent)
		{
			if (n->parent->key > n->key)
				return n->parent;
			else
				return rightAncestor(n->parent);
		}
		return nullptr;
	}
	Node *next(Node *par, const Int &k)
	{
		if (par)
		{
			Node *t = find(par, k);
			if (t->right == nullptr)
				return rightAncestor(t);
			else
				return leftDescendant(t->right);
		}
		return nullptr;
	}
	Node *next(const Int &k)
	{
		return next(root, k);
	}
	Node *next(Node *par)
	{
		if (par)
		{
			if (par->right == nullptr)
				return rightAncestor(par);
			else
				return leftDescendant(par->right);
		}
		return nullptr;
	}
	Node *previous(Node *par, const Int &k)
	{
		if (par)
		{
			Node *t = find(par, k);
			if (t->left == nullptr)
				return leftAncestor(t);
			else
				return rightDescendant(t->left);
		}
		return nullptr;
	}
	Node *previous(const Int &k)
	{
		return previous(root, k);
	}
	Node *previous(Node *par)
	{
		if (par)
		{
			if (par->left == nullptr)
				return leftAncestor(par);
			else
				return rightDescendant(par->left);
		}
		return nullptr;
	}
	vector<Node *> rangeSearch(Node *par, const Int &x, const Int &y)
	{
		Node *t = find(root, x);
		vector<Node *> ret;
		while (t != nullptr and t->key <= y)
		{
			if (t->key >= x)
				ret.push_back(t);
			t = next(t);
		}
		return ret;
	}
	vector<Node *> rangeSearch(const Int &x, const Int &y)
	{
		return rangeSearch(root, x, y);
	}
	Node *remove(Node *par, const Int &k)
	{
		if (par)
		{
			if (par->key == k)
			{
				if (par->right == nullptr)
				{
					Node *t = par->left;
					delete par;
					par = nullptr;
					return t;
				}
				else
				{
					Node *s = leftDescendant(par->right);
					par->key = s->key;
					par->right = remove(par->right, s->key);
					if (par->right)
						par->right->parent = par;
				}
			}
			else if (par->key < k)
			{
				par->right = remove(par->right, k);
				if (par->right)
					par->right->parent = par;
			}
			else if (par->key > k)
			{
				par->left = remove(par->left, k);
				if (par->left)
					par->left->parent = par;
			}
			adjustSize(par);
			return par;
		}
		return nullptr;
	}
	Node *remove(const Int &k)
	{
		root = remove(root, k);
		adjustSize(root);
		return root;
	}
	void adjustSize(Node *n)
	{
		if (n)
		{
			if (n->left == nullptr and n->right == nullptr)
			{
				n->size = 1;
			}
			else if (n->left == nullptr)
			{
				n->size = n->right->size + 1;
			}
			else if (n->right == nullptr)
			{
				n->size = n->left->size + 1;
			}
			else
			{
				n->size = n->left->size + n->right->size + 1;
			}
		}
	}
	Node *orderStatistics(Node *par, const Int &k)
	{
		if (par)
		{
			Int s = 0;
			if (par->left)
				s = par->left->size;
			if (k == s + 1)
			{
				return par;
			}
			else if (k < s + 1)
			{
				if (par->left)
					return orderStatistics(par->left, k);
			}
			else if (k > s + 1)
			{
				if (par->right)
					return orderStatistics(par->right, k - (s + 1));
			}
		}
		return nullptr;
	}
	Node *orderStatistics(const Int &k)
	{
		return orderStatistics(root, k);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	BST bst;
	const Int M = 1e9 + 1;
	Int n, x = 0;
	cin >> n;
	while (n--)
	{
		char t;
		cin >> t;
		if (t == '+')
		{
			Int i;
			cin >> i;
			i = (i % M + x % M) % M;
			bst.insert(i);
		}
		else if (t == '-')
		{
			Int i;
			cin >> i;
			i = (i % M + x % M) % M;
			bst.remove(i);
		}
		else if (t == '?')
		{
			Int i;
			cin >> i;
			i = (i % M + x % M) % M;
			BST::Node *n = bst.find(i);
			if (n != nullptr and n->key == i)
				logn("Found");
			else
				logn("Not found");
		}
		else if (t == 's')
		{
			Int l, r;
			cin >> l >> r;
			l = (l % M + x % M) % M;
			r = (r % M + x % M) % M;
			x = 0;
			vector<BST::Node *> v = bst.rangeSearch(l, r);
			for (auto i : v)
			{
				x = x + i->key;
			}
			logn(x);
		}
	}

	return 0;
}
