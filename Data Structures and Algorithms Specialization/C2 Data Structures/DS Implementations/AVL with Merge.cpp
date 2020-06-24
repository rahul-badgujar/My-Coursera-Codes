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

class AVL
{
  public:
	struct Node
	{
		int key;
		Node *left, *right, *parent;
		int height, size;
		Node(const int &k) : key(k)
		{
			left = right = parent = nullptr;
			height = size = 1;
		}
		~Node()
		{
			key = 0;
			left = right = parent = nullptr;
			size = height = 0;
		}
	};
	Node *root;
	AVL() : root(nullptr)
	{
	}
	AVL(Node *r) : root(r)
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
		adjustHeight(par);
		adjustSize(par);
		int bal = getBalance(par);
		if (bal > 1)
		{
			if (k > par->left->key)
			{
				par->left = rotateLeft(par->left);
			}
			par = rotateRight(par);
		}
		else if (bal < -1)
		{
			if (k < par->right->key)
			{
				par->right = rotateRight(par->right);
			}
			par = rotateLeft(par);
		}
		return par;
	}
	Node *insert(const int &k)
	{
		root = insert(root, k);
		adjustHeight(root);
		adjustSize(root);
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
	static Node *leftDescendant(Node *n)
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
	static Node *rightDescendant(Node *n)
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
	static Node *leftAncestor(Node *n)
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
	static Node *rightAncestor(Node *n)
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
			adjustHeight(par);
			int bal = getBalance(par);
			if (bal > 1)
			{
				if (getBalance(par->left) < 0)
				{
					par->left = rotateLeft(par->left);
				}
				par = rotateRight(par);
			}
			else if (bal < -1)
			{
				if (getBalance(par->right) >= 0)
				{
					par->right = rotateRight(par->right);
				}
				par = rotateLeft(par);
			}
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
	static Node *rotateLeft(Node *n)
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
	static Node *rotateRight(Node *n)
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
	static int getBalance(Node *n)
	{
		if (n)
		{
			if (n->left == nullptr and n->right == nullptr)
			{
				return 0;
			}
			else if (n->left == nullptr)
			{
				return (0 - n->right->height);
			}
			else if (n->right == nullptr)
			{
				return (n->left->height - 0);
			}
			else
			{
				return (n->left->height - n->right->height);
			}
		}
		return 0;
	}
	static void adjustHeight(Node *n)
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
	static void adjustSize(Node *n)
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
	static Node *rebalance(Node *n)
	{
		if (n)
		{
			int bal = getBalance(n);
			if (bal > 1)
			{
				n = rotateRight(n);
				n = rebalance(n);
			}
			else if (bal < -1)
			{
				n = rotateLeft(n);
				n = rebalance(n);
			}
			adjustHeight(n);
			adjustSize(n);
			return n;
		}
		return nullptr;
	}
	static Node *mergeSeparatedWithRoot(Node *R1, Node *R2, Node *R)
	{
		int h1 = 0, h2 = 0;
		if (R1)
			h1 = R1->height;
		if (R2)
			h2 = R2->height;
		if (abs(h1 - h2) <= 1)
		{
			R = joinSeparated(R1, R2, R);
			R = rebalance(R);
			return R;
		}
		else if (h1 > h2)
		{
			R1->right = mergeSeparatedWithRoot(R1->right, R2, R);
			if (R1->right)
				;
			R1->right->parent = R1;
			R1 = rebalance(R1);
			return R1;
		}
		else if (h2 > h1)
		{
			R2->left = mergeSeparatedWithRoot(R1, R2->left, R);
			if (R2->left)
				R2->left->parent = R2;
			R2 = rebalance(R2);
			return R2;
		}
		return nullptr;
	}
	static Node *joinSeparated(Node *R1, Node *R2, Node *R)
	{
		if (R1 == nullptr)
		{
			R->right = R2;
			R2->parent = R;
			return R;
		}
		if (R2 == nullptr)
		{
			R->left = R1;
			R1->parent = R;
			return R;
		}
		if (R2->parent == nullptr)
		{
			R->right = R2;
			R2->parent = R;
			R->left = R1->right;
			if (R1->right)
				R1->right->parent = R;
			R1->right = R;
			R->parent = R1;
			return R1;
		}
		else
		{
			R->left = R1;
			R1->parent = R;
			R->right = R2->left;
			if (R2->left)
				R2->left->parent = R;
			R2->left = R;
			R->parent = R2;
			return R2;
		}
		return nullptr;
	}
	static AVL mergeSeparated(AVL R1, AVL R2)
	{
		if (R1.root == nullptr)
			return R2;
		if (R2.root == nullptr)
			return R1;
		if (R1.root->key > R2.root->key)
		{
			return mergeSeparated(R2, R1);
		}
		AVL resAVL;
		if (R2.root->height > R1.root->height)
		{
			Node *n = leftDescendant(R2.root);
			Node *R = new Node(n->key);
			R2.remove(n->key);
			resAVL.root = mergeSeparatedWithRoot(R1.root, R2.root, R);
		}
		else
		{
			Node *n = rightDescendant(R1.root);
			Node *R = new Node(n->key);
			R1.remove(n->key);
			resAVL.root = mergeSeparatedWithRoot(R1.root, R2.root, R);
		}
		return resAVL;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	AVL a1, a2;

	a1.insert(5);
	a1.insert(3);
	a1.insert(6);

	a2.insert(15);
	a2.insert(10);
	a2.insert(20);
	a2.insert(9);
	a2.insert(11);
	a2.insert(17);
	a2.insert(25);
	a2.insert(8);
	a2.insert(12);
	a2.insert(30);

	logn("AVL A1 : ");
	debVect(a1.getPreorder());

	logn("AVL A2 : ");
	debVect(a2.getPreorder());

	AVL r = AVL::mergeSeparated(a1, a2);

	logn("AVL R : ");
	debVect(r.getPreorder());

	return 0;
}