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

template <typename T, typename L = int>
class MaxHeap
{
  private:
	vector<T> values;
	L size;

	L parentOf(const L &i) const
	{
		return (i - 1) / 2;
	}
	L leftOf(const L &i) const
	{
		return 2 * i + 1;
	}
	L rightOf(const L &i) const
	{
		return 2 * i + 2;
	}
	void shiftUp(const L &i)
	{
		if (i > 0 and i < size)
		{
			L par = parentOf(i);
			if (values[i] > values[par])
			{
				swap(values[i], values[par]);
				shiftUp(par);
			}
		}
	}
	void shiftDown(const L &i)
	{
		if (i < size and i >= 0)
		{
			L mInd = i;
			L l = leftOf(i);
			L r = rightOf(i);
			if (l < size and values[mInd] < values[l])
				mInd = l;
			if (r < size and values[mInd] < values[r])
				mInd = r;
			if (i != mInd)
			{
				swap(values[i], values[mInd]);
				shiftDown(mInd);
			}
		}
	}
	void makeHeap()
	{
		for (L i = size / 2 - 1; i >= 0; i--)
		{
			shiftDown(i);
		}
	}

  public:
	MaxHeap()
	{
		size = 0;
	}
	MaxHeap(const vector<T> &v)
	{
		size = v.size();
		values.resize(size);
		for (L i = 0; i < size; i++)
			values[i] = v[i];
		makeHeap();
	}
	MaxHeap(const T arr[], const L &n)
	{
		size = n;
		values.resize(size);
		for (L i = 0; i < size; i++)
			values[i] = arr[i];
		makeHeap();
	}
	const L &getSize() const
	{
		return size;
	}
	const T &getTop() const
	{
		return values[0];
	}
	const vector<T> &getValues() const
	{
		return values;
	}
	void insert(const T &e)
	{
		values.push_back(e);
		shiftUp(size++);
	}
	const T &popTop()
	{
		T res = values[0];
		swap(values[0], values[--size]);
		shiftDown(0);
		return res;
	}
	void remove(const L &i)
	{
		if (i < size and i >= 0)
		{
			swap(values[i], values[--size]);
			if (i > 0)
			{
				L par = parentOf(i);
				if (values[i] > values[par])
				{
					shiftUp(i);
				}
				else
				{
					shiftDown(i);
				}
			}
		}
	}
	void changePriority(const L &i, const T &newVal)
	{
		if (i >= 0 and i < size)
		{
			L oldVal = values[i];
			values[i] = newVal;
			if (newVal > oldVal)
				shiftUp(i);
			else
				shiftDown(i);
		}
	}
	static void heapSort(vector<T> &v)
	{
		MaxHeap mxHeap;
		L n = v.size();
		for (auto e : v)
			mxHeap.insert(e);
		for (L i = n - 1; i >= 0; i--)
		{
			v[i] = mxHeap.popTop();
		}
	}
	static const vector<T> &buildHeap(const vector<T> &v)
	{
		MaxHeap mxHeap(v);
		return mxHeap.values;
	}
	static const T *&buildHeap(const T arr[], const L &n)
	{
		MaxHeap mxHeap(arr, n);
		static T res[n];
		for (L i = 0; i < n; i++)
			res[i] = mxHeap.values[i];
		return res;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> v{6, 9, 3, 7, 4, 8, 2};
	MaxHeap<int> mxHeap(v);
	logn(mxHeap.popTop());
	debVect(mxHeap.getValues());

	return 0;
}
