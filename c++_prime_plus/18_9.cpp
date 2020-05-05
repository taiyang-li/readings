#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;  
// definition for 0 parameters -- terminating call
void show_list3() {}
// definition for one or more parameters -- recursion
template <typename T, typename... Args>
void show_list3(T value, Args... args) 
{	
	cout << value << endl;  
	show_list3(args...);  
}

int main()
{
	int n = 14;
	double x = 2.71828;
	string mr = "mr string objects"; 
	show_list3(n,x); 
	show_list3(x*x, '!', 7, mr);
	system("pause");
	return 0;
}




