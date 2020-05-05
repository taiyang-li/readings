#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2
{
	public:
		typedef int * ptr_int;
		Array2(int m=1, int n=1)
		{
			_m = m;
			_n = n;
			_matrix = new ptr_int[m];
			for (int i=0; i<_m; i++)
			{
				_matrix[i] = new int[n];
			}
		}

		~Array2()
		{
			if (_matrix == NULL)
			{
				return;
			}

			for (int i=0; i<_m; i++)
			{
				delete []_matrix[i];
			}
			delete []_matrix;
		}	

		Array2& operator=(const Array2& other) 
		{
			if (_matrix != NULL)
			{
				for (int i=0; i<_m; i++)
				{
					delete []_matrix[i];
				}
				delete []_matrix;
			}

			_m = other._m;
			_n = other._n;
			_matrix = new ptr_int[_m];
			for (int i=0; i<_m; i++)
			{
				_matrix[i] = new int[_n];
			}

			for (int i=0; i<_m; i++)
			{
				for (int j=0; j<_n; j++)
				{
					_matrix[i][j] = other._matrix[i][j];
				}
			}
			return *this;
		}
		int operator() (int i, int j) const
		{
			return _matrix[i][j];
		}

		int& operator() (int i, int j)
		{
			return _matrix[i][j];
		}

		int* operator[] (int i)
		{
			return _matrix[i];
		}

	private:
		int _m;
		int _n;
		int** _matrix;
};

int main() {
	Array2 a(3,4);
	int i,j;
	for( i = 0;i < 3; ++i )
		for( j = 0; j < 4; j ++ )
			a[i][j] = i * 4 + j;
	for( i = 0;i < 3; ++i ) {
		for( j = 0; j < 4; j ++ ) {
			cout << a(i,j) << ",";
		}
		cout << endl;
	}
	cout << "next" << endl;
	Array2 b; b = a;
	for( i = 0;i < 3; ++i ) {
		for( j = 0; j < 4; j ++ ) {
			cout << b[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}
