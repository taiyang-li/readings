#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename T>
void my_swap(T &a, T &b);


struct job 
{
	char name[40];
	double salary;
	int floor;
};

// 显示具体化
template<> void my_swap<job>(job &j1, job &j2);
void show(job &j);

int main()
{
	cout.precision(2);
	cout.setf(ios::fixed, ios::floatfield);
	
	int i=10;
	int j=20;
	cout << i << " " << j << endl;
	my_swap(i,j);
	cout << i << " " << j << endl;
	
	job sue = {"susan", 73000.60, 7};
	job sidney = {"sidney", 78060, 9};
	cout << "before job swapping" << endl;
	show(sue);
	show(sidney);
	my_swap(sue, sidney);
	cout << "before job swapping" << endl;	
	show(sue);
	show(sidney);
	
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


template<> void my_swap<job>(job &j1, job &j2)
{
	double t1;
	int t2;
	
	t1 = j1.salary;
	j1.salary = j2.salary;
	j2.salary = t1;
	
	t2 = j1.floor;
	j1.floor = j2.floor;
	j2.floor = t2;
}


void show(job &j)
{
	cout << j.name << endl;
	cout << j.salary << endl;
	cout << j.floor << endl;
	cout << endl;
}


