#include<iostream>
#include<fstream>
using namespace std;
class Matrix
{
	int nrow, ncol;
	double**A;
	int*V;
	void create(int n, int m)
	{

		nrow = n;
		ncol = m;
		A = new double *[nrow];
		for (int i = 0; i < nrow; i++)
			A[i] = new double[ncol];
		V = new int[ncol];
		for (int k = 0; k < ncol; k++)
			V[k] = 0;
	}
	void del()
	{
		for (int i = 0; i < nrow; i++)
			delete[]A[i];
		delete[]A;
		delete[]V;
	}
public:
	void print(ofstream& out)
	{
		out << nrow << " " << ncol << endl;
		for (int i = 0; i < nrow; i++)
		{
			for (int j = 0; j < ncol; j++)
				out << A[i][j] << "\t";
			out << endl;
		}
	}
	Matrix()
	{
		create(2, 2);
	}
	Matrix(const Matrix& B)
	{
		create(B.nrow, B.ncol);
	}
	~Matrix()
	{
		del();
	}
	void input(ifstream& in, ofstream& out)
	{
		int row, col;
		in >> row >> col;
		if (nrow != row || ncol != col)
		{
			del();
			create(row, col);
		}
		for (int i = 0; i < nrow; i++)
			for (int j = 0; j < ncol; j++)
				in >> A[i][j];
		print(out);
	}
	void Sum(const Matrix& X, const Matrix& Y, ofstream& out)
	{
		if (X.nrow != Y.nrow || X.ncol != Y.ncol)
		{
			out << "Bad Dimensions to Sum" << endl;
			return;
		}
		del();
		create(X.nrow, X.ncol);
		for (int i = 0; i < nrow; i++)
			for (int j = 0; j < ncol; j++)
				A[i][j] = X.A[i][j] + Y.A[i][j];
		out << "Sum:" << endl;
		print(out);
	}
	void Sub(const Matrix& X, const Matrix& Y, ofstream& out)
	{
		if (X.nrow != Y.nrow || X.ncol != Y.ncol)
		{
			out << "Bad Dimensions to Subtraction" << endl;
			return;
		}
		del();
		create(X.nrow, X.ncol);
		for (int i = 0; i < nrow; i++)
			for (int j = 0; j < ncol; j++)
				A[i][j] = X.A[i][j] - Y.A[i][j];
		out << "Subtraction:" << endl;
		print(out);
	}
	void Mult_to_el(const Matrix& X, ofstream& out)
	{
		double el;
		cout << "Enter skalar ";
		cin >> el;
		del();
		create(X.nrow, X.ncol);
		for (int i = 0; i < nrow; i++)
			for (int j = 0; j < ncol; j++)
				A[i][j] = X.A[i][j] * el;
		out << "Multiplication by element " << el << ":" << endl;
		print(out);
	}
	void Trans(const Matrix& X, ofstream& out)
	{
		del();
		create(X.ncol, X.nrow);
		for (int i = 0; i < nrow; i++)
			for (int j = 0; j < ncol; j++)
			{
				A[i][j] = X.A[j][i];
			}
		out << "Transpose:" << endl;
		print(out);
	}
	void Mult(const Matrix& X, const Matrix& Y, ofstream& out)
	{
		if (X.nrow != Y.ncol || X.ncol != Y.nrow)
		{
			out << "Bad Dimensions to Multiplication" << endl;
			return;
		}
		del();
		create(X.nrow, Y.ncol);
		for (int i = 0; i < X.nrow; i++)
			for (int j = 0; j < X.nrow; j++)
			{
				int s = 0;
				for (int k = 0; k<X.ncol; k++)
					s += X.A[i][k] * Y.A[k][j];
				A[i][j] = s;
			}
		out << "Multiplication:" << endl;
		print(out);
	}
	double det(int i)
	{
		if (i == nrow - 1)
			for (int j = 0; j < ncol; j++)
				if (V[j] == 0)
					return A[i][j];
		int sign = 1;
		double sum = 0;
		for (int j = 0; j < ncol; j++)
		{
			if (V[j] == 0)
			{
				V[j] = 1;
				sum += A[i][j] * sign*det(i + 1);
				sign = -sign;
				V[j] = 0;
			}
		}
		return sum;
	}
};
int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	Matrix X;
	Matrix A;
	Matrix B;
	A.input(in, out);
	B.input(in, out);
	X.Sum(A, B, out);
	X.Sub(A, B, out);
	X.Mult_to_el(A, out);
	X.Trans(A, out);
	X.Mult(A, B, out);
	out << "Determinant: " << A.det(0) << endl;
	system("pause");
	return 0;
}