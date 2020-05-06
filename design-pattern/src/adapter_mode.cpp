#include <iostream>
using namespace std;

class Deque 
{
	public:
		void push_back(int x)
		{
			cout << "push back x" << endl;
		}

		void push_front(int x)
		{
			cout << "push front x" << endl;
		}

		void pop_back()
		{
			cout << "pop back" << endl;
		}

		void pop_front()
		{
			cout << "pop front " << endl;
		}
};

class Sequence
{
	public:
		virtual void push(int x) = 0;
		virtual void pop() = 0;
};

class Stack : public Sequence
{
	public:
		void push(int x)
		{
			deque.push_back(x);
		}
		
		void pop()
		{
			deque.pop_back();
		}
	private:
		Deque deque;
};

class Queue : public Sequence 
{
	public:
		void push(int x)
		{
			deque.push_front(x);
		}
		
		void pop()
		{
			deque.pop_front();
		}

	private:
		Deque deque;
};

int main()
{
	Stack s;
	Queue q;

	s.push(1);
	s.pop();

	q.push(2);
	q.pop();

	return 0;


}
