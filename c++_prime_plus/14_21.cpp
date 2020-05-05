#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <queue>

using namespace std;

template<class Type>
class Stack
{
private:
	enum {SIZE = 10};
	int stacksize;              // STACKSIZE表示栈的容量
	Type *items;  // 动态分配内存
	int top;                  // top表示栈的大小
public:
	explicit Stack(int ss = SIZE);
	explicit Stack(const Stack &st);
	~Stack();
	bool isempty();
	bool isfull();
	bool push(const Type &item);
	bool pop(Type &item);
	Stack& operator =(const Stack &st);
};

template<class Type> 
Stack<Type> :: Stack(int ss): stacksize(ss), top(0)
{
	items = new Type[stacksize];
}

template<class Type> 
Stack<Type>::Stack(const Stack &st)
{	
	top = st.top;
	stacksize = st.stacksize;
	items = new Type[stacksize];
	for (int i=0; i<top; i++)
		items[i] = st.items[i];
}

template<class Type>
Stack<Type>::~Stack()
{
	delete [] items;
}


template<class Type> 
bool Stack<Type>::isfull()
{	
	return top == stacksize;
}


template<class Type>
bool Stack<Type>::isempty()
{
	return top == 0;
}


template<class Type>
bool Stack<Type>::push(const Type &item)
{
	if (top < stacksize)
	{
		items[top++] = item;
		return true;
	}
	else
	{
		cout << "stack is full" << endl;
		return false;
	}
}

template<class Type>
bool Stack<Type>::pop(Type &item)
{
	if (top > 0)
	{
		item = items[--top];
		return true;
	}
	else
	{
		cout << "stack is empty" << endl;
		return false;
	}
}


template<class Type>
Stack<Type>& Stack<Type>:: operator =(const Stack<Type> &st)
{
	if (this ==&st)
		return *this;
	delete [] items;
	stacksize = st.stacksize;
	top = st.top;
	items = new Type[stacksize];
	for (int i=0; i<top; i++)
		items[i] = st.items[i];
	return *this;
}



template <template <typename T> class Thing>
class Crab
{
private:
	Thing<int> s1;
	Thing<double> s2;
public:
	Crab() {};
	bool push(int a, double b) {
		return s1.push(a) && s2.push(b); }
	bool pop(int &a, double &b) {
		return s1.pop(a) && s2.pop(b);}
};


int main()
{
	Crab<Stack> nebula;
	int ni;
	double nb;
	cout << "enter int double pairs" << endl;
	while (cin >> ni >> nb && ni > 0 && nb > 0)
	{
		if (!nebula.push(ni, nb))
			break;
	}
	while (nebula.pop(ni, nb))
		cout << ni << ", " << nb << endl;
	cout << "Done" << endl;
	return 0;
}
