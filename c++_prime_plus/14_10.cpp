#include <iostream>
#include <cstdio>
#include <string>


using namespace std;



class Worker
{
private:
	string fullname;
	long id;
protected:
	virtual void Data() const;
	virtual void Get();
public:
	Worker() : fullname("no one"), id(0L) {}
	Worker(const string &s, long n): fullname(s), id(n) {}
	virtual ~Worker() = 0 ;
	virtual void Set() = 0;
	virtual void Show() const = 0;
};


class Waiter: virtual public Worker
{
private:
	int panache;
protected:
	void Data() const;
	void Get();  
public:
	Waiter() : Worker(), panache(0) {}
	Waiter(const string &s, long n, int p=0) : Worker(s,n), panache(p) {}
	Waiter(const Worker &wk, int p=0) : Worker(wk), panache(p) {}
	void Set();            // 多态
	void Show() const;    // 多态
};


class Singer: virtual public Worker
{
protected:
	enum {other, alto, contralto, soprano, base, baritone, tenor};
	enum {Vtypes=7};
	void Data() const;
	void Get();
private:
	static char *pv[Vtypes];
	int voice;
public:
	Singer() : Worker(), voice(other) {}
	Singer(const string &s, long n, int v=0) : Worker(s,n), voice(v) {} 
	Singer(const Worker &wk, int v=0) : Worker(wk), voice(v) {}
	void Set(); 
	void Show() const;
};


class SingingWaiter: public Singer, public Waiter
{
protected:
	void Data() const;
	void Get();
public:
	SingingWaiter() {} 
	SingingWaiter(const string &s, long n, int p=0, int v=other) :
		Worker(s,n), Waiter(s, n, p), Singer(s, n, v) {} 
	SingingWaiter(const Worker &wk, long p=0, int v = other) :
		Worker(wk), Waiter(wk, p), Singer(wk, v) {}
	
	SingingWaiter(const Waiter  &wk, int v = other) :
		Worker(wk), Waiter(wk), Singer(wk, v) {};
	SingingWaiter(const Singer &wk, int p=0) :
		Worker(wk), Waiter(wk, p), Singer(wk) {} 
	void Set();
	void Show() const;
};

void Worker::Data() const
{
	cout << "Name: " << fullname << endl;
	cout << "Employee ID: " << id << endl;
}

void Worker::Get() 
{
	cout << "enter worker's name: ";
	getline(cin, fullname);
	cout << "enter worker's id: ";
	cin >> id;
	while (cin.get() != '\n')
		continue;
}


void Waiter::Set()
{
	cout << "enter waiters panache rating: ";
	Worker::Get();
	Get();
}



void Waiter::Show() const 
{
	cout << "category: waiter " << endl;
	Worker::Data();
	Data();
}

void Waiter::Data() const
{
	cout << "waiter panache: " << panache << endl;
}

void Waiter::Get()
{
	cout << "enter waiter's panache rating: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;
}




Worker::~Worker() {} 


// static member
char *Singer::pv[] = {"other", "alto", "contralto", "soprano", "base", "baritone", "tenor"};

void Singer::Set()
{
	cout << "enter singer's name:" ;
	Worker::Get();
	Get();
}
	

	 
void Singer::Show() const
{
	cout << "category: singer" << endl;
	Worker::Data();
	Data();
}

void Singer::Data() const
{
	cout << "vocal range " << pv[voice] << endl;
}

void Singer::Get() 
{
	int i;
	cout << "enter number of singer's vocal range" << endl;
	for (i=0; i<Vtypes; i++)
	{
		cout << i << " " << pv[i] << " ";
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

// SingingWaiter methods
void SingingWaiter::Data() const
{
	Singer::Data();
	Waiter::Data();
}

void SingingWaiter::Get() 
{
	Waiter::Get();
	Singer::Get();
}

void SingingWaiter::Set()
{
	cout << "enter singing waiter's name: ";
	Worker::Get();
	Get();
}

void SingingWaiter::Show() const
{
	cout << "category: singing waiter\n";
	Worker::Data();
	Data();
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
