#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;


double means(double a, double b);
double hmean(double a, double b);
double gmean(double a, double b);




class bad_hmean
{
private:
	double a;
	double b;
public:
	bad_hmean(double x, double y): a(x), b(y) {}
	void mesg()
	{
		cout << "wrong input of funtion hmean" << a << " and " << b << endl;
	}
};


class bad_gmean
{
private:
	double a;
	double b;
public:
	bad_gmean(double x, double y): a(x), b(y) {}
	void mesg() 
	{
		cout << "wrong input of function gmean" << a << " and " << b << endl; 
	}
};


class demo
{
private:
	string word;
public:
	demo (const string &str)
	{
		word = str;
		cout << "demo " << word << " created" << endl;
	}
	~demo()
	{
		cout << "demo " << word << " destroyed" << endl;
	}

	void show() const
	{
		cout << "demo " << word << " lives" << endl;
	}
};




int main()
{
	double x,y,z;
	cout << "enter 2 numbers" << endl;
	while (cin >> x >> y)
	{ 
		try 
		{
			z = means(x,y);
			cout << "means result of " << x << " and " << y << " is " << z << endl;
			cout << "enter the next pair of number" << endl;
		}
		catch(bad_hmean &bg) 
		{
			bg.mesg();
			cout << "try again" << endl;
			continue;
		}
		catch (bad_gmean &bg)
		{
			bg.mesg();
			cout << "sorry, you don't get to play anymore" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}



double hmean(double a, double b)
{
	if (a == -b) 
		throw bad_hmean(a,b);

	return  2.0*a*b/(a+b);
}


double gmean(double a, double b)
{
	if (a <0  || b < 0)
		throw bad_gmean(a,b);
	return sqrt(a*b);
}



double means(double a, double b)
{
	double am, hm, gm;
	demo d2("found in means()");
	am  = (a + b)/2.0;
	try
	{
		hm  = hmean(a,b); 
		gm  = gmean(a,b);
	}
	catch (bad_hmean &bh)
	{
		bh.mesg();
		cout << "caught in means()" << endl;
		throw; // 表示重新发送同一个异常
	}
	d2.show();
	return (am+hm+gm)/3.0;
}












