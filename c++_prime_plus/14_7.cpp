#include <iostream>
#include <cstdio>
#include <string>


using namespace std;



class Worker
{
private:
	string fullname;
	long id;
public:
	Worker() : fullname("no one"), id(0L) {}
	Worker(const string &s, long n): fullname(s), id(n) {}
	virtual ~Worker() = 0 ;
	virtual void Set();
	virtual void Show() const;
};


class Waiter: public Worker
{
private:
	int panache;
public:
	Waiter() : Worker(), panache(0) {}
	Waiter(const string &s, long n, int p=0) : Worker(s,n), panache(p) {}
	Waiter(const Worker &wk, int p=0) : Worker(wk), panache(p) {}
	void Set();            // 多态
	void Show() const;    // 多态
};


class Singer: public Worker
{
public:
	enum {other, alto, contralto, soprano, base, baritone, tenor};
	enum {Vtypes=7};
private:
	static char *pv[Vtypes];
	int voice;
public:
	Singer() : Worker(), voice(other) {}
	Singer(const string &s, long n, int v=0) : Worker(s,n), voice(v) {} 
	Singer(const Worker &wk, int v=0) : Worker(wk), voice(v) {}
	void Set(); 
	void Show()  const; 
};

void Worker::Set() 
{
	cout << "enter worker's name: ";
	getline(cin, fullname);
	cout << "enter worker's id: ";
	cin >> id;
	while (cin.get() != '\n')
		continue;
}


void Worker::Show() const 
{
	cout << "Name: " << fullname << endl;
	cout << "ID: " << id << endl;
}



void Waiter::Set()
{
	Worker::Set();
	cout << "enter waiters panache rating: ";
	cin >> panache; 
	while(cin.get() != '\n')
		continue;
}


void Waiter::Show() const 
{
	cout << "category: waiter " << endl;
	Worker::Show();
	cout << "panache ratings" << panache << endl;
}

Worker::~Worker() {} 


// static member
char *Singer::pv[] = {"other", "alto", "contralto", "soprano", "base", "baritone", "tenor"};

void Singer::Set()
{
	int i;
	Worker::Set();
	cout << "enter number of singer's vocal range" << endl;
	for (i=0; i<Vtypes; i++)
	{
		cout << i << " " << pv[i] << endl;
		if (i%4 == 3)
			cout << endl;
	}
	if (i%4 != 0)
		cout << endl;
	while(cin >> voice && (voice < 0 || voice >= Vtypes))
	{
		cout << "please enter a value >= 0 and <= Vtypes";
	}
	while (cin.get() != '\n')
		continue;
		
}


	 
void Singer::Show() const
{
	cout << "category: singer" << endl;
	Worker::Show();
	cout << "vocal range: " << pv[voice] << endl; 
}



const int LIM = 4;
int main()
{	
	Waiter bob("Bob Apple", 314L, 5);
	Singer bev("Bevery Hills", 522L, 3);
	Waiter w_temp;
	Waiter s_temp;
	
	Worker *pw[LIM] = {&bob, &bev, &w_temp, &s_temp};
	
	for (int i=0; i<LIM; i++)
	{
		pw[i]->Set();
	}

	for (int i=0; i<LIM; i++)
	{
		pw[i]->Show();
		cout << endl;
	}
	return 0;
}
