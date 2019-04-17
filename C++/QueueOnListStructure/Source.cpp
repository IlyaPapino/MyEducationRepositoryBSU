#include<iostream>
using namespace std;
class Empty {};
struct node
{
	int info;
	node*next;
	node(int x)
	{
		info = x;
		next = 0;
	}
};
class Q_List
{
	node*first;
	node*last;
public:
	Q_List()
	{
		first = last = 0;
	}
	Q_List(const Q_List&q)
	{
		node*t;
		t = q.first;
		while (t != 0)
		{
			node*d = new node(t->info);
			if (last != 0)
				last->next = d;
			else
				first = d;
			last = d;
			t = t->next;
		}
	}
	~Q_List()
	{
		while (first != 0)
			pop_front();
	}
	void push_back(int x)
	{
		node*d=new node(x);
		if (last != 0)
			last->next = d;
		else
			first = d;
		last = d;
	}
	void pop_front()
	{
		if (first == 0)
			throw Empty();
		if (first == last&&first != 0)
		{
			first = last = 0;
			return;
		}
		node*old = first;
		first = first->next;
		delete old;
	}
	Q_List& operator=(const Q_List&q)
	{
		if (this == &q)
			return *this;
		node*t;
		t = q.first;
		while (t != 0)
		{
			node*d = new node(t->info);
			if (last != 0)
				last->next = d;
			else
				first = d;
			last = d;
			t = t->next;
		}

	}
	void print()
	{
		node*tmp = first;
		while (tmp != 0)
		{
			cout << tmp->info<<" ";
			tmp = tmp->next;
		}
		cout << endl;
	}
};
int main()
{
	try
	{
		Q_List A;
		Q_List B;
		A.push_back(1);
		A.print();
		A.push_back(2);
		A.print();
		A.push_back(3);
		A.print();
		A.pop_front();
		A.print();
		B = A;
		B.print();
		A.pop_front();
		A.print();
		A.pop_front();
		A.print();
		A.pop_front();
		A.print();
	}
	catch (Empty)
	{
		cout << "Is empty" << endl;
	}
	system("pause");
	return 0;

}