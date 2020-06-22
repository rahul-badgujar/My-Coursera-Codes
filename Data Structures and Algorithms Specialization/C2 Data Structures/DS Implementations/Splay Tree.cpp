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

class SplayTree
{
  public:
	struct Node
	{
		int key;
		Node *left, *right, *parent;
		int height;
		int size;
		Node(const int &k) : key(k)
		{
			left = right = parent = nullptr;
			size = height = 1;
		}
		~Node()
		{
			key = 0;
			size = height = 0;
			left = right = parent = nullptr;
		}
	};
	Node *root;
	SplayTree() : root(nullptr)
	{
	}
	Node *splayFind(Node *par, const int &k)
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
				if (k > par->right->key)
				{
					par->right->right = splayFind(par->right->right, k);
					par = rotateLeft(par);
				}
				else if (k < par->right->key)
				{
					par->right->left = splayFind(par->right->left, k);
					par->right = rotateRight(par->right);
				}
				par = rotateLeft(par);
			}
			else if (par->key > k)
			{
				if (par->left == nullptr)
					return par;
				if (k < par->left->key)
				{
					par->left->left = splayFind(par->left->left, k);
					par = rotateRight(par);
				}
				else if (k > par->left->key)
				{
					par->left->right = splayFind(par->left->right, k);
					par->left = rotateLeft(par->left);
				}
				par = rotateRight(par);
			}
			adjustSize(par);
			adjustHeight(par);
			return par;
		}
		return nullptr;
	}
	Node *find(Node *par, const int &k)
	{
		par = splayFind(root, k);
		adjustSize(par);
		adjustHeight(par);
		return par;
	}
	Node *find(const int &k)
	{
		root = find(root, k);
		return root;
	}
	Node *insert(Node *par, const int &k)
	{
		if (par == nullptr)
		{
			par = new Node(k);
			return par;
		}
		else
		{
			par = find(k);
			if (par->key == k)
				return par;
			Node *n = new Node(k);
			if (k < par->key)
			{
				n->right = par;
				par->parent = n;
				if (par->left)
				{
					n->left = par->left;
					par->left = nullptr;
					n->left->parent = n;
				}
			}
			else if (k > par->key)
			{
				n->left = par;
				par->parent = n;
				if (par->right)
				{
					n->right = par->right;
					par->right = nullptr;
					n->right->parent = n;
				}
			}
			adjustSize(par);
			adjustHeight(par);
			adjustSize(n);
			adjustHeight(n);
			return n;
		}
		return nullptr;
	}
	Node *insert(const int &k)
	{
		root = insert(root, k);
		adjustSize(root);
		adjustHeight(root);
		return root;
	}
	vector<int> getInorder(Node *par)
	{
		vector<int> elem;
		if (par)
		{
			vector<int> L = getInorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			elem.push_back(par->key);
			vector<int> R = getInorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
		}
		return elem;
	}
	vector<int> getInorder()
	{
		return getInorder(root);
	}
	vector<int> getPreorder(Node *par)
	{
		vector<int> elem;
		if (par)
		{
			elem.push_back(par->key);
			vector<int> L = getPreorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			vector<int> R = getPreorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
		}
		return elem;
	}
	vector<int> getPreorder()
	{
		return getPreorder(root);
	}
	vector<int> getPostorder(Node *par)
	{
		vector<int> elem;
		if (par)
		{
			vector<int> L = getPostorder(par->left);
			elem.insert(elem.end(), L.begin(), L.end());
			vector<int> R = getPostorder(par->right);
			elem.insert(elem.end(), R.begin(), R.end());
			elem.push_back(par->key);
		}
		return elem;
	}
	vector<int> getPostorder()
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
			par = find(par, k);
			if (par->key != k)
				return par;
			Node *temp = par;
			Node *childL = par->left;
			Node *childR = par->right;
			if (childL == nullptr)
			{
				par = childR;
			}
			else
			{
				par = find(childL, k);
				par->right = childR;
				childR->parent = par;
			}
			delete temp;
			childR = childL = temp = nullptr;
			adjustSize(par);
			adjustHeight(par);
			return par;
		}
		return nullptr;
	}
	Node *remove(const int &k)
	{
		root = remove(root, k);
		adjustSize(root);
		adjustHeight(root);
		return root;
	}
	void adjustHeight(Node *n)
	{
		if (n)
		{
			if (n->left == nullptr and n->right == nullptr)
			{
				n->height = 1;
			}
			else if (n->left == nullptr)
			{
				n->height = n->right->height + 1;
			}
			else if (n->right == nullptr)
			{
				n->height = n->left->height + 1;
			}
			else
			{
				n->height = max(n->left->height, n->right->height) + 1;
			}
		}
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
	Node *rotateLeft(Node *n)
	{
		if (n)
		{
			Node *m = n->right;
			if (m == nullptr)
				return n;
			Node *b = m->left;
			m->left = n;
			n->parent = m;
			n->right = b;
			if (b)
				b->parent = n;
			adjustHeight(n);
			adjustHeight(m);
			adjustSize(n);
			adjustSize(m);
			return m;
		}
		return nullptr;
	}
	Node *rotateRight(Node *n)
	{
		if (n)
		{
			Node *m = n->left;
			if (m == nullptr)
				return n;
			Node *b = m->right;
			m->right = n;
			n->parent = m;
			n->left = b;
			if (b)
				b->parent = n;
			adjustHeight(n);
			adjustHeight(m);
			adjustSize(n);
			adjustSize(m);
			return m;
		}
		return nullptr;
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
	SplayTree st;
	st.insert(50);
	st.insert(30);
	st.insert(20);
	st.insert(40);
	debVect(st.getPreorder());
	log(endl);
	st.remove(20);
	logn(st.root->key);
	debVect(st.getPreorder());
	log(endl);
	return 0;
}
