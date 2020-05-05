#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template <iostream>
T lesser(T a, T b)
{
	return a < b ? a :b;
}

int lesser(int a, int b)
{
	a = a < 0 ? (-a) : a;
	b = b < 0 ? (-b) : b;
	return a < b ? a : b;
}
int main()
{
	int m = 30;
	int n = 20;
	double x = 15.9;
	double y = 25.9;
	
	cout << lesser(m,n) << endl;
	cout << lesser(x,y) << endl;
	cout << lesser<>(m,n) << endl;    
	cout << lesser<int>(x,y) << endl;  // 显示实例化 

	system("pause");
	return 0;
}
