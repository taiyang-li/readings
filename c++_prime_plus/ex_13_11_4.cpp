#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>

using namespace std;

class Port
{
private:
	char *brand;
	char style[20];
	int bottles;
public:
	Port(const char *br = "none", const char *st = "none", int b=0)
	{
		brand = new char[strlen(br) + 1];
		strcpy(brand, br);
		strcpy(style, st);
		bottles = b;
	}
	
	Port(const Port &p)
	{
		brand = new char[strlen(p.brand) + 1];
		strcpy(brand, p.brand);
		strcpy(style, p.style);
		bottles = p.bottles;
	}

	virtual ~Port() {
		delete [] brand;
	}
	
	Port& operator =(const Port &p)
	{
		if (this == &p)
			return *this;
		brand = new char[strlen(p.brand) + 1];
		strcpy(brand, p.brand);
		strcpy(style, p.style);
		bottles = p.bottles;
		return *this;
	}

	Port& operator +=(int b)
	{
		bottles += b;
		return *this;
	}
	
	Port& operator -=(int b)
	{
		bottles -= b;
		return *this;  
	}
	
	int BottleCount() const {return bottles;}
	
	virtual void Show() const
	{
		cout << "brand: " << brand << endl;
		cout << "style: " << style << endl;
		cout << "bottles:" << bottles << endl;
	}
	
	friend ostream& operator <<(ostream &os, const Port &p)
	{
		os << p.brand << ", " << p.style << ", " << p.bottles << endl;
		return os;
	}
};

class VintagePort : public Port
{
private:
	char *nickname;
	int year;
public:
	VintagePort() : Port()  
	{
		nickname = new char[30];
		strcpy(nickname, "none");
		year = 0;
	}
	
	VintagePort(const char *br, int b, const char *nn, int y)
		: Port(br, "none", b), year(y)
	{
		nickname = new char(strlen(nn)+1);
		strcpy(nickname, nn);
	}

	VintagePort(const VintagePort &vp) : Port(vp) 
	{
		nickname = new char(strlen(vp.nickname)+1); 
		strcpy(nickname, vp.nickname);
		year = vp.year;
	}
	
	virtual ~VintagePort() {delete [] nickname;}
	
	VintagePort& operator =(const VintagePort &vp) 
	{
		if (this == &vp)
			return *this;
		Port::operator =(vp);
		nickname = new char(strlen(vp.nickname)+1); 
		strcpy(nickname, vp.nickname);
		year = vp.year;
		return *this;
	}
	void Show() const
	{
		Port::Show();
		cout << "nickname: " << nickname << endl;
		cout << "year: " << year << endl;
	}
	
	friend ostream& operator <<(ostream &os, const VintagePort &vp)
	{
		os << (const Port &)vp << ", " << vp.nickname << ", " << vp.year;
	}
}; 

int main()
{
	Port a("wiskey", "hehe", 10);
	a.Show();
	
	Port b(a);
	b.Show();
	b += 200;
	b.Show();
	b -= 100;
	b.Show();
	
	VintagePort c("wiskey", 100, "water", 1995);
	c.Show();
	
	system("pause");
	return 0;

}









