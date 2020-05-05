#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>




using namespace std;

template<class Type>
class Stack
{
private:
	enum {MAX = 10};
	Type items[MAX];
	int top;
public:
	Stack();
	bool isempty();
	bool isfull();
	bool push(const Type &item);
	bool pop(Type &item);
};

template<class Type>
Stack<Type>::Stack()
{
	top = 0;
}

template<class Type>
bool Stack<Type>::isempty()
{
	return (top == 0);
}

template<class Type>
bool Stack<Type>::isfull()
{
	return top == MAX;
}


template<class Type>
bool Stack<Type>::push(const Type &item)
{
	if (top < MAX)
	{
		items[top++] = item;
		return true;
	}
	else
		return false;
}

template<class Type>
bool Stack<Type>::pop(Type &item)
{
	if (top > 0)
	{
		item =  items[--top];
		return true;
	}
	else
		return false;
}


// 使用模板类


int main()
{
	Stack<string> st;
	char ch;
	string po;
	cout << "enter A to add a purchase order" << endl;
	cout << "enter P to process a PO or Q to quit" << endl;
	
	while(cin>>ch && toupper(ch) != 'Q')
	{
		while(cin.get() != '\n')
			continue;
		if (!isalpha(ch))
		{
			cout << "\a" << endl;
			continue;
		}

		switch(ch)
		{
			case 'A':
			case 'a':
				cout << "enter a po number to add" << endl;
				cin >> po;
				if (st.isfull())
					cout << "stack already full" << endl;
				else
					st.push(po);
				break;
			case 'p':
			case 'P':
				if (st.isempty())
					cout << "stack already empty" << endl;
				else
				{
					st.pop(po);
					cout << "pop element: " << po << endl;
				}	
				break;
			default:
				cout << "wrong input" << endl;
		}
		cout << "enter A to add a purchase order" << endl;
		cout << "enter P to process a PO or Q to quit" << endl;
	}
	cout << "Bye" << endl;
	return 0;
}
