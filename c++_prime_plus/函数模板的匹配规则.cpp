#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename T>
void ShowArray(T arr[], int n);

template<typename T>
void ShowArray(T *arr[], int n);

struct debte
{
	char name[50];
	double  amount;
};

int main()
{
	int things[6] = {13, 31, 103, 301, 310, 130};
	struct debte mr_E[3] = 
	{
		{"hehe1", 2400.0},
		{"hehe2", 2410.0},
		{"hehe3", 1800.0}
	};
	double *pd[3];
	for (int i=0; i<3; i++)
		pd[i] = &mr_E[i].amount;
	cout << "Listing Mr mr_E counts of things" << endl;
	ShowArray(things, 6);
	cout << "Listing Mr mr_E debts " << endl;
	ShowArray(pd, 3);
	system("pause");
	return 0;
}


template<typename T>
void ShowArray(T arr[], int n)
{
	cout << "template A" << endl;
	for (int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

template<typename T>
void ShowArray(T *arr[], int n)
{
	cout << "template B" << endl;
	for (int i=0; i<n; i++)
		cout << *arr[i] << " ";
	cout << endl;
}



