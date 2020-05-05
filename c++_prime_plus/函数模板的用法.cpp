#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename T>
void my_swap(T &a, T &b);

template<typename T>
void my_swap(T *a, T *b, int n);

template<typename T>
void show_arr(T *arr, int n);

int main()
{
	int i=30;
	int j=20;
	cout << i << " " << j << endl;
	my_swap(i,j);
	cout << i << " " << j << endl;

	double a = 1.2;
	double b = 2.1;
	cout << a << " " << b << endl;
	my_swap(a,b);
	cout << a << " " << b << endl;
	

	float arr1[3] = {1.0, 2.0, 3.0};
	float arr2[3] = {1.5, 2.5, 3.5};
	show_arr(arr1, 3);
	show_arr(arr2, 3);
	my_swap(arr1, arr2, 3);
	show_arr(arr1, 3);
	show_arr(arr2, 3);
	

	system("pause");
	return 0;
}

template<typename T>
void my_swap(T &a, T &b)
{
	T t;
	t = a; 
	a = b;
	b = t;
}


template<typename T>
void my_swap(T *a, T *b, int n)
{
	T temp;
	for (int i=0; i<n; i++)
	{
		temp = a[i]; 
		a[i] = b[i];
		b[i] = temp;
	}
}


template<typename T>
void show_arr(T *arr, int n)
{
	if (arr== NULL || n <=0)
		return;
	for (int i=0; i<n; i++)
		cout << arr[i] << "\t" ;
	cout << endl;
}



