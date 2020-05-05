#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int (*func)(int a, int b);

int f_add(int a, int b)
{
	return a+b;
}

int f_sub(int a, int b)
{
	return a-b;
}

int f_mul(int a, int b)
{
	return a*b;
}

int f_div(int a, int b)
{
	return a/b;
}

int main()
{
	int op1;
	int op2;
	char op;
	
	cin >> op1 >> op2 >> op;

	switch(op)
	{
		case '+':
			func = f_add;
			break;
		case '-':
			func = f_sub;
			break;
		case '*':
			func = f_mul;
			break;
		case '/':
			if (op2 == 0)
			{
				cout << "Divided by zero!" << endl;
				return 0;
			}		
			func = f_div;
			break;
		default:
			cout << "Invalid operator!" << endl;
			return 0;
	}
	cout << func(op1, op2) << endl;
	return 0;
}
