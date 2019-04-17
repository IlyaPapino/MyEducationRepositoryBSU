#include <iostream>
using namespace std;
class BadDimension {};
class MyArr
{
	int n;//кол-во элементов в массиве
	int*A;//массив
	int my_cmp(const void* p1, const void*p2)
	{
		int*a = (int*)p1;
		int*b = (int*)p2;
		return *a - *b;
	};
public:
	MyArr()
	{
		n = 2;
		A = new int[2];
	}
	MyArr(int n0)
	{
		n = n0;
		A = new int[n0];
	}
	MyArr(const MyArr&B)
	{
		n = B.n;
		A = new int[B.n];
		for (int i = 0; i < n; i++)
			A[i] = B.A[i];
	}
	~MyArr()
	{
		delete[]A;
	}
	MyArr& operator=(const MyArr&B)
	{
		if (this == &B)
			return *this;
		delete[]A;
		A = new int[B.n];
		n = B.n;
		for (int i = 0; i < n; i++)
			A[i] = B.A[i];
		return*this;
	}
	friend istream &operator>>(istream &cin, MyArr &B)
	{
		delete[]B.A;
		cin >> B.n;
		B.A = new int[B.n];
		for (int i = 0; i < B.n; i++)
			cin >> B.A[i];
		return cin;
	}
	friend ostream &operator<<(ostream &cout, MyArr &B)
	{
		for (int i = 0; i < B.n; i++)
		{
			cout << B.A[i] << " ";
		}
		cout << endl;
		return cout;
	}
	MyArr operator+(const MyArr&B)
	{
		if (n != B.n)
			throw BadDimension();
		MyArr b(*this);
		for (int i = 0; i < n; i++)
			b.A[i] += B.A[i];
		return b;
	}
	void min_max(int &indmax, int &indmin)
	{
		indmax = indmin = 0;
		for (int i = 1; i < n; i++)
		{
			if (A[i] > A[indmax])
				indmax = i;
			else indmin = i;
		}
	}
	MyArr Freq()
	{
		MyArr Y(n);
		for (int i = 0; i < n; i++)
		{
			Y.A[i] = 0;
			for (int j = 0; j < n; j++)
				if (A[i] == A[j])
					Y.A[i]++;
		}
		return Y;
	}
	/*void Freq2(MyArr &El, MyArr&F)
	{
	MyArr T(n + 1);
	for (int i = 0; i < n; i++)
	T.A[i] = A[i];
	T.A[n + 1] = 2147483647;
	qsort(T.A, T.n, sizeof(int), my_cmp);
	int c = 1, k = 0;
	for (int i = 0; i < n; i++)
	{
	if (T.A[i] == T.A[i + 1])
	c++;
	else
	{
	El.A[k] = T.A[i];
	F.A[k] = c;
	c = 1;
	k++;
	El.n = k;
	F.n = k;
	}
	}
	}*/
};
int main()
{
	MyArr C;
	MyArr D;
	cin >> C;
	cout << C;
	D = C;
	cout << D;
	MyArr E;
	try
	{
		E = C + D;
		cout << E;
	}
	catch (BadDimension)
	{
		cout << "BadDimension" << endl;
	}
	int max, min;
	E.min_max(max, min);
	cout << max << " " << min << endl;
	E = E.Freq();
	cout << E;
	system("pause");
	return 0;
}