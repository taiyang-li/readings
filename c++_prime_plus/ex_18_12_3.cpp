#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;  

long double sum_value() {return 0.0;}
template <typename T, typename... Args>
int sum_value(T value, Args... args)
{
	return value + sum_value(args);
}
	

int main()
{
	// MS2010不支持可变参数模板
	cout << sum_value(10, 1.0, 'a', 'y') << endl;
	system("pause");
	return 0;
}




