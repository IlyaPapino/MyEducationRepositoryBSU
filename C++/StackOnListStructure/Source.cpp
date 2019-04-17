#include<iostream>
using namespace std;
class Empty{};
class Stack
{
	struct Link
	{
		int data;
		Link* next;
		Link(int dat, Link*net)
		{
			data = dat;
			next = net;
		}
	};
	Link* head;
public:
	Stack()
	{
		head = NULL;
	}
	Stack(const Stack&q)
	{
		head = q.head;
	}
	void push(int dat)
	{
		head = new Link(dat, head);
	}
	int pop()
	{
		if (head == 0)
		{
			throw Empty();
		}
		int res = head->data;
		Link*old = head;
		head = head->next;
		delete old;
		return res;
	}
	Stack& operator=(const Stack&q)
	{
		if (this == &q)
			return *this;
		head = q.head;
		return *this;
	}
	int peek()
	{
		if (head == NULL)
		{
			throw Empty();
		}
		return head->data;
	}
	~Stack()
	{
		while (head != NULL)
		   pop();
	}
	void print()
	{
		Link*tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->data<<" ";
			tmp = tmp->next;
		}
		cout << endl;
	}
};
int main()
{
	try
	{
		Stack A;
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
	catch (Empty)
	{
		cout << "Is Empty" << endl;
	}
	system("pause");
	return 0;
}