#include <iostream>
#include <cstdlib>

using namespace std;

// 模板参数 
template <class T, int n>
class ArrayTP
{
private:
	T ar[n];
public:
	ArrayTP() {};
	explicit ArrayTP(const T &v);
	virtual T& operator [](int i);
	virtual T operator [](int i) const;
};


template<class T, int n>
ArrayTP<T, n>::ArrayTP(const T &v)
{
	for (int i=0; i<n; i++)
		ar[i] = v;
}

template<class T, int n>
T& ArrayTP<T, n>::operator [](int i)
{
	if (i<0 || i>n)
	{
		cerr << "error in array limits: " << i
			<< " is out of memory" << endl;
		exit(EXIT_FAILURE);
	}
	else	
		return ar[i];
}


template<class T, int n>
T  ArrayTP<T, n>::operator [](int i) const
{
	if (i<0 || i>n)
	{
		cerr << "error in array limits: " << i
			<< " is out of memory" << endl;
		exit(EXIT_FAILURE);
	}
	else	
		return ar[i];
}



int main()
{
	ArrayTP<int ,10> sums;
	ArrayTP<double, 10> aves;
	ArrayTP<ArrayTP<int, 5>, 10> twodee;
	
	int i,j;
	
	for (i=0; i<10; i++)        
	{
		sums[i] = 0;
		for (j=0; j<5; j++)
		{
			twodee[i][j] = (i+1) * (j+1);
			sums[i] += twodee[i][j];
		}	
		aves[i] = (double) sums[i] / 5;
	}

	for (i=0; i<10; i++)
	{
		for (j=0; j<5; j++)
		{
			cout.width(2);
			cout << twodee[i][j] << " ";
		}
		cout << " sum: " << sums[i];
		cout.width(3);
		cout << ", average: " << aves[i];
		cout << endl;
	}
	
	cout << "Done" << endl;
	return 0;
}



