#include<iostream>
using namespace std;
class Full {};
class Empty {};
class A_stack
{
	int A_size;
	int*A_ptr;
	int top;
	bool Is_Empty()
	{
		return (top == 0);
	}
	bool Is_Full()
	{
		return(top >= A_size);
	}
public:
	A_stack()
	{
		A_ptr = new int[5];
		A_size = 5;
		top = 0;
	}
	A_stack(int _size)
	{
		A_ptr = new int[_size];
		A_size = _size;
		top = 0;
	}
	A_stack(const A_stack&S)
	{
		A_size = S.A_size;
		A_ptr = new int[A_size];
		top = S.top;
		for (int i = 0;i < S.top;i++)
			A_ptr[i] = S.A_ptr[i];
	}
	~A_stack()
	{
		delete[]A_ptr;
	}
	A_stack& operator=(const A_stack&S)
	{
		if (this == &S)
			return *this;
		delete[]A_ptr;
		A_size = S.A_size;
		A_ptr = new int[A_size];
		top = S.top;
		for (int i = 0;i < top;i++)
			A_ptr[i] = S.A_ptr[i];
		return *this;
	}
	void push(int n)
	{
		if (top >= A_size)
		{
			throw Full();
		}
		A_ptr[top] = n;
		top++;
	}
	int pop()
	{
		if (top == 0)
			throw Empty();
		else 
		{
			return A_ptr[--top];
		}
	}
	void print()
	{
		int tmp = top;
		while (tmp != 0)
			cout << A_ptr[--tmp]<<" ";
		cout << endl;
	}
};
int main()
{
	try 
	{
		A_stack A(3);
		A.push(1);
		A.print();
		A.push(2);
		A.print();
		A.push(3);
		A.print();
		A.pop();
		A.print();
		A.pop();
		A.print();
		A.pop();
		A.print();
		A.pop();
		A.print();
	}
	catch (Full)
	{
		cout << "Is Full"<<endl;
	}
	catch (Empty)
	{
		cout << "Is Empty" << endl;
	}
	system("pause");
	return 0;
}