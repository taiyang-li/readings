#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>


using namespace std;

class Cpmv
{
public:
	struct Info
	{
		string qcode;
		string zcode;
	};
private:
	Info *pi;
public:
	Cpmv();
	Cpmv(string q, string z); 
	Cpmv(const Cpmv &cp);
	Cpmv(Cpmv &&mv);
	~Cpmv();
	Cpmv & operator =(const Cpmv &cp); // 左值引用
	Cpmv & operator =(Cpmv &&mv);      // 右值引用 
	Cpmv operator +(const Cpmv &obj) const;
	void Display() const;
};

Cpmv::Cpmv()
{
	pi = new Info;
	pi->qcode = "";
	pi->zcode = "";
	cout << "default constructer" << endl;
}

Cpmv::Cpmv(string q, string z) 
{
	pi = new Info;
	pi->qcode = q;
	pi->zcode = z;
	cout << "common constructer" << endl;
}

Cpmv::Cpmv(const Cpmv &cp)
{
	pi = new Info;
	pi->qcode = cp.pi->qcode;
	pi->zcode = cp.pi->zcode;
	cout << "copy constructer" << endl;
}

Cpmv::Cpmv(Cpmv &&mv)
{
	pi = mv.pi;
	mv.pi= nullptr;
	cout << "move constructer" << endl;
}


Cpmv::~Cpmv()
{
	delete pi;
	cout << "destructer" << endl;
}


Cpmv & Cpmv::operator =(const Cpmv &cp) // 左值引用
{
	if (this != &cp)
	{
		pi->qcode = cp.pi->qcode;
		pi->zcode = cp.pi->zcode;
	}
	cout << "entering operator =()" << endl;
	return *this;
}

Cpmv & Cpmv::operator =(Cpmv &&cp)
{	
	if (&cp != this)
	{
		delete pi;
		pi = cp.pi;   
		cp.pi = nullptr;
	}
	cout << "entering operator +()" << endl;
	return  *this;
}


Cpmv Cpmv::operator +(const Cpmv &obj) const 
{
	Cpmv res(pi->qcode+obj.pi->qcode, pi->zcode+obj.pi->zcode);
	cout << "entering operator +()" << endl;
	return res;
}


void Cpmv::Display() const
{
	cout << "qcode: " << pi->qcode << endl;
	cout << "zcode: " << pi->zcode << endl;
	cout << "entering function display" << endl;
	cout << endl;
}


int main()
{
	Cpmv one;                 
	one.Display();
	Cpmv two("li", "yang");
	two.Display();

	Cpmv three(two);
	three.Display();

	Cpmv four(two+three);
	four.Display();
	
	three = four;
	three.Display();

	four = two + three;
	four.Display();
	
	system("pause");
	return 0;

}















