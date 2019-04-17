#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cctype>   
#include <cstdlib>
#include<fstream>
using namespace std;
struct Books
{
	char* B_Name;
	char* B_Author;
	int B_Year;
	int B_Num;
	Books()
	{
		B_Name = new char[100];
		B_Author = new char[100];
		B_Year = 2000;
		B_Num = 10000;
	}
	Books(Books&B)
	{
		B_Name = new char[100];
		strcpy(B_Name, B.B_Name);
		B_Author = new char[100];
		strcpy(B_Author, B.B_Author);
		B_Year = B.B_Year;
		B_Num = B.B_Num;
	}
	~Books()
	{
		delete []B_Name;
		delete []B_Author;
	}
	Books& operator=(const Books& B)
	{
		if (this == &B)
			return *this;
		B_Name = new char[100];
		strcpy(B_Name, B.B_Name);
		B_Author = new char[100];
		strcpy(B_Author, B.B_Author);
		B_Year = B.B_Year;
		B_Num = B.B_Num;
		return *this;
	}
	friend istream& operator>>(istream& in, Books& B)
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
	friend ostream& operator<<(ostream& out, const Books& B)
	{
		out << B.B_Author << " " << B.B_Name << " " << B.B_Year << " " << B.B_Num << endl;
		return out;
	}
	friend void Write_Books(ofstream&out, Books&A)
	{
		out.write((char*)&A, sizeof(Books));
	}
	friend bool operator==(Books& one, Books &two) 
	{
		if (one.B_Num == two.B_Num) 
			return true;
		return false;
	}
	friend bool operator>(Books& one, Books &two) 
	{
		if (one.B_Num > two.B_Num) 
			return true;
		return false;
	}
	friend bool operator>=(Books& one, Books &two)
	{
		if (one.B_Num >= two.B_Num)
			return true;
		return false;
	}
 
};
template<class T>
class Set
{
	T *items;
	int size;
	int capacity;
	void enlargeCapacity()
	{
		capacity *= 2;
		T* tmp = new T[capacity];
		for (int i = 0; i < size; i++)
			tmp[i] = items[i];
		delete[] items;
		items = tmp;
	}
public:
	Set()
	{
		capacity = 16;
		items = new T[capacity];
		size = 0;
	}

	Set(int aCapacity)
	{

		capacity = aCapacity;
		items = new T[aCapacity];
		size = 0;
	}

	Set(const Set<T>& B)
	{
		size = B.size;
		capacity = B.capacity;
		items = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			items[i] = B.items[i];
		}
	}

	~Set()
	{
		delete[]items;
	}

	Set& operator=(const Set<T>& B)
	{
		if (&B == this)
			return *this;
		size = B.size;
		capacity = B.capacity;
		items = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			items[i] = B.items[i];
		}
		return *this;
	}
	friend istream& operator >>(istream& in, Set<T>& B)
	{
		in >> B.size;
		if (B.size > B.capacity) 
		{
			delete[]B.items;
			B.capacity = B.size * 2;
			B.items = new T[B.capacity];
		}
		in.ignore();
		for (int i = 0; i < B.size; i++)
			in >> B.items[i];
		return in;
	}

	friend ostream& operator <<(ostream& out, Set<T>& B)
	{
		for (int i = 0; i < B.size; i++)
			out << B.items[i] << " ";
		return out;
	}
	friend void Write(fstream&out,Set<T>&A)
	{
		out.write((char*)&A.size, sizeof(int));
		out.write((char*)A.items, A.size * sizeof(T));
	}
	friend void Read(fstream&in, Set<T>&A)
	{
		in.read((char*)&A.size, sizeof(int));
		in.read((char*)A.items, A.size * sizeof(T));
	}
	void Add(T& a)
	{
		int i = 0;
		while (a > items[i] && size > i) 
			i++;
		if (i <= size && (items[i] == a)==false)
		{
			if (size + 1 > capacity)
				enlargeCapacity();
			for (int j = size; j > i; j--)
				items[j] = items[j-1];
			items[i] = a;
			size++;
		}
	}
	friend Set<T> operator+ (Set &a, Set& b)//Объединение
	{
		int i, j, k;
		i = j = k = 0;
		Set c(a.size + b.size);
		while (i < a.size && j < b.size)
		{
			if (b.items[j]>a.items[i] )
			{
				c.items[k] = a.items[i];
				i++;
				k++;
			}
			else
				if (a.items[i] == b.items[j])
				{
					c.items[k] = a.items[i];
					j++;
					k++;
					i++;
				}
				else
				{
					c.items[k] = b.items[j];
					k++;
					j++;
				}
		}
		while (i < a.size)
		{
			c.items[k++] = a.items[i++];
		}
		while (j < b.size)
		{
			c.items[k++] = b.items[j++];
		}
		c.size = k;
		return c;
	}
	friend Set<T> operator *(Set& B, Set& C)//Пересечение
	{
		int i = 0, j = 0, k = 0;
		int num;
		if (B.size < C.size)
			num = B.size;
		else
			num = C.size;
		Set D(num);
		while (i < B.size && j < C.size)
		{
			if (C.items[j] > B.items[i]) 
				i++;
			else 
				if (B.items[i] > C.items[j]) 
				j++;
			else 
			{
				D.items[k] = B.items[i];
				i++;
				j++;
				k++;
			}
		}
		D.size = k;

		return D;
	}
	friend Set<T> operator -(Set<T>& B, Set<T>& C)//Разность
	{
		int sizeB = B.size;
		int sizeC = C.size;
		int num = B.size - C.size;
		fabs(num);
		int k = 0;
		Set<T> D(sizeB);
		for (int i = 0; i < sizeB; i++) 
		{
			int j = 0;
			while (j < sizeC && !(C.items[j] == B.items[i])) 
				j++; 
			if (j == sizeC) 
			{
				D.Add(B.items[i]);
				k++;
			}
		}
		return D;
	}
	friend Set<T> operator %(Set<T> &B, Set<T> &C)//Симметричная разность
	{
		int sizeB = B.size;
		int sizeC = C.size;
		int k = 0;
		Set<T> D(sizeB+sizeC);
		int c = 0;
		for (int i = 0; i < sizeB; i++)
		{
			int j = 0, k = 0;
			while (!(C.items[j] == B.items[i]) && j < sizeC) 
				j++;
			//while ((D.items[k] == B.items[i])==false && k < c)
			//	k++;
			if (j == sizeC)// && k == c) 
				D.Add(B.items[i]);
		}
		for (int i = 0; i < sizeC; i++)
		{
			int j = 0, k = 0;
			while (!(B.items[j] == C.items[i]) && j < sizeB) 
				j++;
			//while ((D.items[k] == C.items[i])==false && k < c) 
			//	k++;
			if (j == sizeB)// && k == c) 
				D.Add(C.items[i]);
		}
		return D;
	}
};
int main()
{
	setlocale(LC_ALL, "RUS");
	fstream in("in.txt");
	fstream in_two("in_two.txt");
	fstream in_bin;
	in_bin.open("bin.bin", ios::binary|ios::in|ios::out);
	Set<int> A;
	Set<int> B;
	Set<int> C;
	int a;
	cin >> A;
	cin >> B;
	cin >> a;
	A.Add(a);
	C = A + B;
	cout << C<<endl;
	Write(in_bin, C);
	Read(in_bin, C);
	C = A * B;
	cout << C<<endl;
	C = B - A;
	cout << C<<endl;
	C = A % B;
	cout << C<<endl;
	system("pause");
	in_bin.close();
	return 0;
}