#include<iostream>
using namespace std;
class Empty {};
class Full {};
class Queue
{
	int*A;
	int last;
	int first;
	int size;
	int n;
	bool Is_Full()
	{
		if (n == size&&n != 0)
			return true;
		else
			return false;
	}
	bool Is_Empty()
	{
		if (n == 0)
			return true;
		else
			return false;
	}
public:
	Queue()
	{
		size = 5;
		A = new int[size];
		first = last = 0;
		n = 0;
	}
	Queue(const Queue& B)
	{
		size = B.size;
		A = new int[size];
		first = B.first;
		last = B.last;
		n = B.n;
		for (int i = 0; i < size; i++)
			A[i] = B.A[i];
	}
	Queue(int _size)
	{
		A = new int[_size];
		first = last = 0;
		n = 0;
		size = _size;
	}
	~Queue()
	{
		delete[]A;
	}
	Queue& operator=(const Queue&B)
	{
		if (this == &B)
			return *this;
		delete[]A;
		size = B.size;
		A = new int[size];
		first = B.first;
		last = B.last;
		n = B.n;
		for (int i = 0; i < size; i++)
			A[i] = B.A[i];
		return *this;
	}
	void pushback(int n1)
	{
		if (!Is_Full())
		{
			A[last] = n1;
			last = (last + 1) % size;
			n++;
		}
		else
		{
			throw Full();
		}
	}
	void popfront()
	{
		if (!Is_Empty())
		{
			int t = A[first];
			first = (first + 1) % size;
			n--;
			if (n == 0)
				first = last = 0;
		}
		else
		{
			throw Empty();
		}
	}
	void print()
	{
		int ind = first;
		for (int i = 0; i < n; i++)
		{
			cout << A[ind] << " ";
			ind = (ind + 1) % size;
		}
		cout << endl;
	}
};
int main()
{
	try
	{
		Queue A(3);
		A.pushback(1);
		A.print();
		A.pushback(2);
		A.print();
		A.pushback(3);
		A.print();
		A.popfront();
		A.print();
		A.pushback(4);
		A.print();
		A.popfront();
		A.print();
		A.popfront();
		A.print();
		A.pushback(5);
		A.print();
		A.popfront();
		A.print();
		A.popfront();
		A.print();
		A.popfront();
		A.print();
		A.popfront();
		A.print();
	}
	catch (Empty)
	{
		cout << "Is Empty" << endl;
	}
	catch (Full)
	{
		cout << "Is Full" << endl;
	}
	system("pause");
	return 0;
}