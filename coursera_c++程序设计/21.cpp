#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T>
class CArray1D
{
	public:
		CArray1D() : _p(NULL) {}
		~CArray1D()
		{
			delete[] _p;
		}
		void set(int a)
		{
			_p = new T[a];
			_a = a;
		}
		T& operator[](int i) const
		{
			return _p[i];
		}
	private:
		T* _p;
		int _a;
};

template <class T>
class CArray2D
{

	public:
		CArray2D() : _p(NULL)
	{
	}

		~CArray2D()
		{
			delete[] _p;
		}

		void set(int b, int a)
		{
			_p = new CArray1D<T>[b];
			for (int i=0; i<b; i++)
			{
				_p[i].set(a);
			}
			_b = b;
		}

		CArray1D<T>& operator[](int i)
		{
			return _p[i];
		}
	private:
		CArray1D<T>* _p;
		int _b;


};

template <class T>
class CArray3D
{
	public:
		CArray3D(int c, int b, int a)
		{
			_p = new CArray2D<T>[c];
			for (int i=0; i<c; i++)
			{
				_p[i].set(b, a);
			}
			_c = c;
		}

		~CArray3D()
		{
			delete[] _p; 
		}

		CArray2D<T>& operator[](int i) const
		{
			return _p[i];
		}

	private:
		CArray2D<T>* _p;
		int _c;
};

int main()
{
	CArray3D<int> a(3,4,5);
	int No = 0;
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 4; ++j )
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 4; ++j )
			for( int k = 0; k < 5; ++k )
				cout << a[i][j][k] << ",";
	return 0;
}
