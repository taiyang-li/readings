#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime> 

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


// main function
const int Num = 10;
int main()
{
	srand(time(0));
	cout << "Please enter stack size: ";	
	int stacksize;
	cin >> stacksize;
	Stack<const char *> st(stacksize);
	
	const char * in[Num] = {"1: litaiwen", "2: limeiling", 
				"3: litaiting", "4: litaixing",
				"5: litaiping", "6: liyang",
				"7: wubangzheng", "8: wuchunyan",
	                        "9: weixingxing", "10: weijianmei"};
	const char *out[Num];


	int processed = 0;  // 表示输入idx
	int nextin = 0;     // 表示输出idx
	while(processed < Num)
	{
		if (st.isempty())
			st.push(in[nextin++]);
		else if (st.isfull())
			st.pop(out[processed++]);
		else if (rand() % 2 && nextin < Num)
			st.push(in[nextin++]);
		else 
			st.pop(out[processed++]);
	}

	for (int i=0; i<Num; i++)
		cout << out[i] << endl;
	
	cout << "Bye"; 
	return 0;
}
