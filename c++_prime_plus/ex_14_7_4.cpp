#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Person
{
private:
	string fname;
	string lname;
public:
	Person() : fname("none"), lname("none") {}
	Person(const string &fn, const string &ln) 
		: fname(fn), lname(ln) {}
	virtual void Show();
	virtual ~Person() = 0;   
};
 
Person::~Person() {}

void Person::Show()   
{
	cout << "first name: " << fname << endl;
	cout << "last name: " << lname << endl;
}

class Gunslinger : virtual public Person
{
private:
	double dtime;
	int nick_no; 
public:
	Gunslinger() 
		: Person(), dtime(0.0), nick_no(0) {}
	
	Gunslinger(const string &fn, const string &ln, double d, int n)
		: Person(fn, ln), dtime(d), nick_no(n) {}

	Gunslinger(const Person &p, double d, int n)
		: Person(p), dtime(d), nick_no(n) {}

	void Show();
	double Draw();
};

double Gunslinger::Draw() {return dtime;}

void Gunslinger::Show()   
{
	Person::Show();
	cout << "time of drawing gun: " << dtime << endl;
	cout << "nick number of gun: " << nick_no << endl;
}

class PokerPlayer : virtual public Person
{ 
	int card_val; 
public:
	PokerPlayer() : Person() {} 
	PokerPlayer(const string &fn, const string &ln, int c) 
		: Person(fn, ln), card_val(c) {}
	PokerPlayer(const Person &p, int c) : Person(p), card_val(c) {}
	
	void Set()
	{
		card_val = 1 + rand() % 52;
	}
	void Show()
	{
		Person::Show();
		cout << "card number: " << card_val << endl;
	}
	int Draw()
	{
		return card_val;
	}
};

class BadDude : public Gunslinger, public PokerPlayer
{
public:
	BadDude() : Person(), Gunslinger(), PokerPlayer() {}
	BadDude(const string &fn, const string &ln, double d, int n, int c)
		: Person(fn ,ln), Gunslinger(fn, ln, d, n), PokerPlayer(fn, ln, c) {}
	BadDude(const Person &p, double d, int n, int c)
		: Person(p), Gunslinger(p, d, n),PokerPlayer(p, c) {}
	BadDude(const Gunslinger &g, int c)
		: Person(g), Gunslinger(g), PokerPlayer(g, c){}
	BadDude(const PokerPlayer &po, double d, int n)
		: Person(po), Gunslinger(po, d, n), PokerPlayer(po) {}
	
	BadDude(const Gunslinger &g, const PokerPlayer &po)
		: Person(po), Gunslinger(g), PokerPlayer(po) {}

	double Gdraw() { return Gunslinger::Draw();}
	int Cdraw() { return PokerPlayer::Draw();} 
	void Show() 
	{
		Person::Show();
		cout << "time of drawing gun: " << Gunslinger::Draw() << endl;
		cout << "card number: " << PokerPlayer::Draw() << endl;

	}
};

int main()
{
	Gunslinger a("li", "yang", 0.21, 5);
	a.Show();
	
	PokerPlayer b("li", "meiling", 25);
	b.Show();
	
	BadDude c(a, b); 
	c.Show();

	system("pause");
	return 0;
}
