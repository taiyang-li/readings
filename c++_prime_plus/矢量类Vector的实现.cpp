#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;



class Vector
{
public:
	// 类中数据类型
	enum Mode {RECT=0, POL};
private:
	double x;
	double y;
	double mag;
	double ang;
	Mode mode; //  极坐标表示还会直角坐标表示
	void set_x();
	void set_y();
	void set_mag();
	void set_ang();
	
public:
	Vector();
	Vector(double n1, double n2, Mode form = RECT);
	void reset(double n1, double n2, Mode form = RECT);
	~Vector();
	double xval() const {return x;}
	double yval() const {return y;}
	double magval() const {return mag;}
	double angval() const {return ang;}
	void polar_mode();
	void rect_mode();

	// 千万不要返回局部变量的引用
	Vector operator +(const Vector &b) const;
	Vector operator -(const Vector &b) const;
	Vector operator -() const;
	Vector operator *(double n) const;
	
	friend Vector operator *(double n, const Vector &a);
	friend ostream& operator <<(ostream& os, Vector &v);
};

void Vector::set_mag()
{	
	mag = sqrt(x*x + y*y);
}

void Vector::set_ang()
{
	// 此处不可取
	if (x == 0.0 && y == 0.0)
		ang = 0.0;
	else
		ang = atan2(y,x);
}

void Vector::set_x()
{
	x = mag * cos(ang);
}

void Vector::set_y()
{
	y = mag * sin(ang);
}

Vector::Vector()
{
	x = y = mag = ang = 0.0;
	mode = RECT;
}

Vector::Vector(double n1, double n2, Mode form)
{
	mode = form;
	if (form == RECT)
	{
		x = n1;
		y = n2;
		set_mag();
		set_ang();
	}
	else if (form == POL)
	{
		mag = n1;
		ang = n2;
		set_x();
		set_y();
	}
	else
	{
		cout << "incorrect 3rd argument to Vector()";
		cout << "vector set to 0" ;
		x = y = mag = ang = 0.0;
		mode = RECT;
	}
}

void Vector::reset(double n1, double n2, Mode form)
{
	mode = form;
	if (form == RECT)
	{
		x = n1;
		y = n2;
		set_mag();
		set_ang();
	}
	else if (form == POL)
	{
		mag = n1;
		ang = n2;
		set_x();
		set_y();
	}
	else
	{
		cout << "incorrect 3rd argument to Vector()";
		cout << "vector set to 0" ;
		x = y = mag = ang = 0.0;
		mode = RECT;
	}
}


Vector::~Vector()
{

}

void Vector::polar_mode()
{
	mode = POL;
}

void Vector::rect_mode()
{
	mode = RECT;
}

Vector Vector::operator +(const Vector &b) const
{
	return Vector(x+b.x, y+b.y);
}

Vector Vector::operator -(const Vector &b) const
{
	return Vector(x-b.x, y-b.y);
}

Vector Vector::operator -() const 
{
	return Vector(-x, -y);
}

Vector Vector::operator *(double n) const 
{
	return Vector(n*x, n*y);
}

Vector operator *(double n, const Vector &a)
{
	return a*n;
}

ostream& operator <<(ostream& os, Vector &v)
{
	if (v.mode == Vector::RECT)
		os << "rect: " << v.x << ", " << v.y << endl;
	else if (v.mode == Vector::POL)
		os << "polar: " << v.mag << ", " << v.ang << endl;
	else
		os << "Vector mode invalid" << endl;
	return os;
}

int main()
{
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0); 
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "enter target distance (q to quit): ";
	while (cin >> target)   // 给定目标
	{
		cout << "enter step length:";
		if (!(cin >> dstep))  // 给定步长
			break;
		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
			cout << steps << ": ";
			cout << result << endl;
		}

		cout << "after " << steps << "steps, the subject " << "has the following location:\n";
		cout << result << endl;
		
		steps = 0;
		result.reset(0.0, 0.0);
		cout << "enter target distance (q to quit): ";
	}
}



