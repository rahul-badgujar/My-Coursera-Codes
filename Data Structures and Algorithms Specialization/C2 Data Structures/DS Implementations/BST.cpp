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
		int key;
		Node *left, *right, *parent;
		int size;
		Node(const int &k) : key(k), size(1)
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
	Node *find(Node *par, const int &k)
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
	Node *find(const int &k)
	{
		return find(root, k);
	}
	Node *insert(Node *par, const int &k)
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
	Node *insert(const int &k)
	{
		root = insert(root, k);
		adjustSize(root);
		return root;
	}
	void printInorder(Node *par)
	{
		if (par)
		{
			printInorder(par->left);
			logs(par->key);
			printInorder(par->right);
		}
	}
	void printInorder()
	{
		printInorder(root);
	}
	void printPreorder(Node *par)
	{
		if (par)
		{
			logs(par->key);
			printPreorder(par->left);
			printPreorder(par->right);
		}
	}
	void printPreorder()
	{
		printPreorder(root);
	}
	void printPostorder(Node *par)
	{
		if (par)
		{
			printPostorder(par->left);
			printPostorder(par->right);
			logs(par->key);
		}
	}
	void printPostorder()
	{
		printPostorder(root);
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
	Node *next(Node *par, const int &k)
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
	Node *next(const int &k)
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
	Node *previous(Node *par, const int &k)
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
	Node *previous(const int &k)
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
	vector<Node *> rangeSearch(Node *par, const int &x, const int &y)
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
	vector<Node *> rangeSearch(const int &x, const int &y)
	{
		return rangeSearch(root, x, y);
	}
	Node *remove(Node *par, const int &k)
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
	Node *remove(const int &k)
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
	Node *orderStatistics(Node *par, const int &k)
	{
		if (par)
		{
			int s = 0;
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
	Node *orderStatistics(const int &k)
	{
		return orderStatistics(root, k);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	BST bst;
	bst.insert(50);
	bst.insert(30);
	bst.insert(20);
	bst.insert(40);
	bst.insert(70);
	bst.insert(60);
	bst.insert(80);
	bst.insert(10);
	bst.insert(100);
	bst.printPreorder();
	log(endl);
	bst.remove(80);
	bst.printPreorder();
	log(endl);
	bst.printInorder();
	log(endl);
	logn(bst.orderStatistics(3)->key);

	return 0;
}