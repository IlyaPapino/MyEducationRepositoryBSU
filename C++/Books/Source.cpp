#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cctype>   
#include <cstdlib>
#include<fstream>
using namespace std;
struct Books_One
{
	char* B_Author;
	char* B_Name;
	int B_Year;
	int B_Col;
	Books_One()
	{
		B_Name = new char[100];
		B_Author = new char[100];
		B_Year = 2000;
		B_Col = 10;
	}
	~Books_One()
	{
		delete B_Name;
		delete B_Author;
	}
	friend istream& operator>>(istream& in,Books_One& B)
	{
		char buff[20];
			in >>B.B_Author >>B.B_Name;
			while (1 < 2)
			{
				int len = strlen(B.B_Name);
				in >> buff;
				if (atoi(buff) != 0)
				{
					B.B_Year = atoi(buff);
					in >>B.B_Col;
					break;
				}
				else
				{
					strcpy(B.B_Name + len, " ");
					strcpy(B.B_Name + len + 1, buff);
				}
			}
		return in;
	}
	friend ostream& operator<<(ostream& out, Books_One& B)
	{
		out << B.B_Author << " " << B.B_Name << " " << B.B_Year << " " << B.B_Col << endl;
		return out;
	}
};
struct Books_Two
{
	char* B_Name;
	char* B_Author;
	int B_Year;
	int B_Num;
	Books_Two()
	{
		B_Name = new char[100];
		B_Author = new char[100];
		B_Year = 2000;
		B_Num = 10000;
	}
	~Books_Two()
	{
		delete B_Name;
		delete B_Author;
	}
	friend istream& operator>>(istream& in, Books_Two& B)
	{
		char buff[20];
		in >> B.B_Author >> B.B_Name;
		while (1 < 2)
		{
			int len = strlen(B.B_Name);
			in >> buff;
			if (atoi(buff) != 0)
			{
				B.B_Year = atoi(buff);
				in >> B.B_Num;
				break;
			}
			else
			{
				strcpy(B.B_Name + len, " ");
				strcpy(B.B_Name + len + 1, buff);
			}
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, Books_Two& B)
	{
		out << B.B_Author << " " << B.B_Name << " " << B.B_Year << " " << B.B_Num << endl;
		return out;
	}
};
class Massiv_Books
{
public:
	virtual	int Find_Books(char*A)
	{
		return 0;
	}
	virtual void My_Sort()
	{}
};
class Massiv_Books_One :public Massiv_Books
{
	Books_One*A;
	int n;
	static int Comporator(const void*p1, const void*p2)
	{
		Books_One*a = (Books_One*)p1;
		Books_One*b = (Books_One*)p2;
		return strcmp(a->B_Author, b->B_Author);
	}
	Books_One* My_Search(char Name[])
	{
		Books_One B;
		strcpy(B.B_Author, Name);
		Books_One* res;
		res = (Books_One*)bsearch(&B, A, n, sizeof(Books_One), Comporator);
		return res;
	}
public:
	Massiv_Books_One()
	{
		A = new Books_One[3];
		n = 3;
	}
	Massiv_Books_One(int col)
	{
		A = new Books_One[col];
		n = col;
	}
	Massiv_Books_One(const Massiv_Books_One& B)
	{
		n = B.n;
		A = new Books_One[n];
	}
	~Massiv_Books_One()
	{
		delete[]A;
	}
	friend istream& operator>>(istream& in, Massiv_Books_One& B)
	{
		for (int i = 0; i < B.n; i++)
			in >>B.A[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, Massiv_Books_One& B)
	{
		for (int i = 0; i < B.n; i++)
			out << B.A[i];
		return out;
	}
	void My_Sort()
	{
		qsort(A, n, sizeof(Books_One), Comporator);
	}
	int Find_Books(char Name[])//колличество книг одного автора
	{
		Books_One* res,*res2;
		res = My_Search(Name);
		res2 = res;
		if (res == 0)
			return 0;
		int c = res->B_Col;
		while (res != A)
		{
			res = res - 1;
			if (strcmp(res->B_Author, Name) != 0)
				break;
			else
				c += res->B_Col;
		}
		while (res2 != A + n-1)
		{
			res2 = res2 + 1;
			if (strcmp(res2->B_Author, Name) != 0)
				break;
			else
				c += res2->B_Col;
		}
		return c;
	}
};
class Massiv_Books_Two :public Massiv_Books
{
	Books_Two* A;
	int n;
	static int Comporator(const void*p1, const void*p2)
	{
		Books_Two*a = (Books_Two*)p1;
		Books_Two*b = (Books_Two*)p2;
		return strcmp(a->B_Name, b->B_Name);
	}
	Books_Two* My_Search(char Name[])
	{
		Books_Two B;
		strcpy(B.B_Name, Name);
		Books_Two* res;
		res = (Books_Two*)bsearch(&B, A, n, sizeof(Books_Two), Comporator);
		return res;
	}
public:
	Massiv_Books_Two()
	{
		A = new Books_Two[3];
		n = 3;
	}
	Massiv_Books_Two(int col)
	{
		A = new Books_Two[col];
		n = col;
	}
	Massiv_Books_Two(const Massiv_Books_Two& B)
	{
		n = B.n;
		A = new Books_Two[n];
	}
	~Massiv_Books_Two()
	{
		delete[]A;
	}
	friend istream& operator>>(istream& in_two, Massiv_Books_Two& B)
	{
		for (int i = 0; i < B.n; i++)
			in_two >> B.A[i];
		return in_two;
	}
	friend ostream& operator<<(ostream& out_two, Massiv_Books_Two& B)
	{
		for (int i = 0; i < B.n; i++)
			out_two << B.A[i];
		return out_two;
	}
	void My_Sort()
	{
		qsort(A, n, sizeof(Books_Two), Comporator);
	}
	int Find_Books(char Name[])//колличество одинаковых книг с разными инвентарными номерами
	{
		Books_Two* res, *res2;
		res = My_Search(Name);
		res2 = res;
		if (res == 0)
			return 0;
		int c = 1;
		while (res != A)
		{
			res = res - 1;
			if (strcmp(res->B_Name, Name) != 0)
				break;
			else
				c++;
		}
		while (res2 != A + n - 1)
		{
			res2 = res2 + 1;
			if (strcmp(res2->B_Name, Name) != 0)
				break;
			else
				c++;
		}
		return c;
	}
};
int main()
{
	setlocale(LC_ALL, "RUS");
	fstream in("in.txt");
	fstream in_two("in_two.txt");
	Massiv_Books_One A(3);
	Massiv_Books_Two B(4);
	in >> A;
	in_two >> B;
	Massiv_Books*C;
	C = &A;
	C->My_Sort();
	int f = C->Find_Books("Пушкин");
	cout << f<<endl;
	C = &B;
	C->My_Sort();
	int k = C->Find_Books("Мёртвые души");
	cout << k<<endl;
	system("pause");
	return 0;
}