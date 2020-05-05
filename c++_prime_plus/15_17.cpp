#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Grand
{
private:
	int hold;
public:
	Grand(int h=0): hold(h) {}
	virtual void Speak() const {cout << "i am a grand class" << endl;}
	virtual int Value() const {return hold;}
};

class Superb : public Grand
{	
public:
	Superb(int h=0): Grand(h) {}
	virtual void Speak() const {cout << "i am a superb class" << endl;}
	virtual void Say() const 
	{
		cout << "I hold the superb value of " << Value() << endl;
	}
};

class Magnificent: public Superb
{
private:
	char ch;
public:
	Magnificent(int h=0, char c='A'): Superb(h) {ch = c;}
	virtual void Speak() const {cout << "i am a magnificent class" << endl;}
	virtual void Say() const 
	{
		cout << "i hold the interger" << Value() << endl;
		cout << "i hold the character" << ch << endl;
	}
};

Grand* GetOne();


int main()
{
	srand(time(0));
	Grand *pg;
	Superb *ps;
	for (int i=0; i<5; i++)
	{
		pg = GetOne();
		pg->Speak();
		if (ps = dynamic_cast<Superb*>(pg))
		{
			ps->Say();
		}
	}
	system("pause");
	return 0;
}


Grand* GetOne()
{
	Grand *p;
	switch (rand() % 3 )
	{
	case 0:
		p = new Grand(rand() % 100);
		break;
	case 1:
		p = new Superb(rand() % 100);
		break;
	case 2:
		p = new Magnificent(rand()%100, 'A'+rand()%26);
		break;
	default:
		cout << "it is impossible" << endl;
	}
	return p;
}





