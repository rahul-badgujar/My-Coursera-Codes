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

struct Node
{
	Int key;
	Node *left, *right;
	Node(const Int &k)
	{
		key = k;
		left = right = nullptr;
	}
};

void inorder(Node *p)
{
	if (p)
	{
		inorder(p->left);
		logs(p->key);
		inorder(p->right);
	}
}
void preorder(Node *p)
{
	if (p)
	{
		logs(p->key);
		preorder(p->left);
		preorder(p->right);
	}
}
void postorder(Node *p)
{
	if (p)
	{
		postorder(p->left);
		postorder(p->right);
		logs(p->key);
	}
}
Node *leftDescendant(Node *p)
{
	if (p)
	{
		if (p->left)
			return leftDescendant(p->left);
		else
			return p;
	}
	return nullptr;
}
Node *rightDescendant(Node *p)
{
	if (p)
	{
		if (p->right)
			return rightDescendant(p->right);
		else
			return p;
	}
	return nullptr;
}
bool isBST(Node *p)
{
	if (p)
	{
		bool ans = true;
		if (p->left)
			ans = ans and rightDescendant(p->left)->key < p->key;
		if (p->right)
			ans = ans and leftDescendant(p->right)->key >= p->key;
		if (ans)
			ans = ans and isBST(p->left);
		if (ans)
			ans = ans and isBST(p->right);
		return ans;
	}
	return true;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Int n;
	cin >> n;
	if (n == 0)
	{
		logn("CORRECT");
		return 0;
	}
	Node *arr[n];
	for (Int i = 0; i < n; i++)
		arr[i] = new Node(-1);
	for (Int i = 0; i < n; i++)
	{
		Int k, l, r;
		cin >> k >> l >> r;
		arr[i]->key = k;
		if (l != -1)
			arr[i]->left = arr[l];
		if (r != -1)
			arr[i]->right = arr[r];
	}
	Node *root = arr[0];
	if (isBST(root))
		logn("CORRECT");
	else
		logn("INCORRECT");
	return 0;
}
