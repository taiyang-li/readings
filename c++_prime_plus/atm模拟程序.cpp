#include <iostream>
#include <cstream>
#include <cstdlib>
#include <ctime>


using namespace std;

class Customer
{
private:
	long arrive;  // arrival time for customer
	int processtime;  // processing time for customer
public:
	Customer() {arrive = processtime = 0;}
	void set(long when);
	long when() const {return arrive;}
	int ptime() const {return processtime;}
};


void Customer::set(long when)
{
	processtime = rand() % 3;
	arrive = when;
}


typedef Customer Item;




class Queue
{
	enum {Q_SIZE = 10;}
private:
	// later
	struct Node {Item item; struct Node *next;}
	enum {Q_SIZE = 10};
	Node *front;
	Node *rear;
	int items;             // cur length
	const int qsize;       // maximum length
public:
	Queue(int qs = Q_SIZE);
	Queue(const Queue &q);     // to add
	Queue& operator =(const Queue &q) {return *this;} // to add
	
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
};



Queue::Queue(int qs = Q_SIZE) : qsize(qs)
{
	rear = NULL;
	front = NULL;
	items = 0;
}

bool Queue::isempty() const 
{
	return items == 0;
}

bool Queue::isfull() const 
{
	return items == qsize;
}

int Queue::queuecount() const 
{
	return items;
}


bool Queue::enqueue(const Item &item)  // add item to queue
{		
	if (isfull())
		return false;
	
	Node *add = new Node;
	add->item = item;
	add->next = NULL;

	items++;
	if (front == NULL)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::dequeue(Item &item)
{
	if (front == NULL)
		return false;
	
	item = front->item;
	items--;
	
	Node *temp = front;
	front = front->next;
	delete temp;
	

	// 只有一个元素
	if (items == 0)
		rear = NULL;
	return true;
}


Queue::~Queue()
{
	Node *temp;
	while(front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}



const int MIN_PER_HR = 60;

bool newcustomer(double x); 

int main()
{
	int qs;
	cin >> qs;
	Queue line(qs);
	
	int hours;
	cin >> hours;
	long cyclelimit = MIN_PER_HR * hours;
	
	double perhour;
	cin >> perhour;
	double min_per_cust;
	min_per_cust = MIN_PER_HR/ perhour;
	
	Item temp;
	long turnaways = 0;  // turned away by full queue
	long customers = 0;  // joined the queue
	long served = 0;     // served during the simulation 
	long sum_line = 0;   // 
	int wait_time = 0;
	long line_wait = 0;


	for (int cycle = 0; cycle = cyclelimit; cycle++)
	{
		if (newcustomer(min_per_cust))
		{
			if (line.isfull())
				turnaways++;
			else
			{
				customer++;
				temp.set(cycle);
				line.enqueue(temp);
			}
		}

		if(wait_time <= 0 && !line.isempty())
		{
			line.dequeue(temp);
			wait_time = temp.ptime();
			line_wait  += cycle-temp.when();
			served++;
		}
		if (wait_time > 0)
			wait_time--;
		sum_line += line.queuecount();
	}
	if (customers > 0)
	{
		cout << cutomers << "accepted" << endl;
		cout << served << "served" << endl;
		cout << turnaways << "turnaways" << endl;
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		
	}
	else
		cout << "no cutomer" << endl;
	
	cout << "Done" << endl;
}




bool newcutomer(double x)
{
	return (rand()*x/RAND_MAX < 1); 
}
