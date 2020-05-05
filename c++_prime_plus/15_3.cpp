#include <cstdio>
#include <iostream>
#include <string>

using namespace std;


template <class Item> class QueueTP
{
private:
	enum {Q_SIZE = 10};            // 这只是一种数据类型而已，并没有多少意义
	// Node is a nested class definition
	class  Node
	{
	public:
		Item item;
		Node *next;
		Node(const Item &i): item(i), next(NULL) {}  
	};


	Node *front;
	Node *rear;
	int items;                 // 表示队列大小
	const int qsize;           // 表示容量
	// QueueTP(const QueeueTP &q): qsize(0) {}
	// QueueTP& operator =(const QueueTP &q) {return *this};
public:
	// constructor 
	QueueTP(int qs = Q_SIZE): qsize(qs)
	{
		items = 0;
		front = NULL;
		rear = NULL;
	}
	
	// destructor
	~QueueTP()
	{
		Node *temp;
		while(front != NULL)
		{
			temp = front;
			front = front->next;
			delete temp;
		}			
	}
	// is full
	bool isempty() {return items == 0;}

	// is empty 
	bool isfull() {return items == qsize;}

	// queuecount
	int queuecount() {return items;}
	// enqueue   入队
	bool enqueue(const Item &item)
	{
		if (items == qsize)
			return false;
		
		Node *add = new Node(item);
		if (front == NULL)
			front = add;
		else
			rear->next = add;
		rear = add;
		++items;
		return true;
	}
	
	// dequeue
	bool dequeue(Item &item)
	{
		if (qsize == 0)
			return false;

		item = front->item;
		Node *temp = front;
		front = front->next;
		delete temp;
		if (front == NULL)
			rear = front;
		
		--items;
		return true;
	}	 
};


int main()
{
	QueueTP<string> cs(5);     // 注意不是数组
	string temp;

	while (!cs.isfull())
	{
		cout << "please enter your name" << endl;
		getline(cin, temp);
		cs.enqueue(temp);
	}
	
	while (!cs.isempty())
	{
		cs.dequeue(temp);
		cout << "now processing " << temp << "..." << endl;
	}


	getchar();
	return 0;
}
