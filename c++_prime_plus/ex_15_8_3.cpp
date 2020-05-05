#include <iostream>
#include <cmath> // or math.h, unix users may need -lm flag
#include <stdexcept>

using namespace std;

class bad_hmean : public exception       // bad_hmean的异常处理类
{
private:
	double a;
	double b;
public: 
	bad_hmean(double _a, double _b) : a(_a), b(-b) {} 
    void mesg()
	{   
		cout << "hmean of " << a << " and " << b << " failed" << endl;
		cout << "function: hmean(), error: denominator should not be 0" << endl;
	}
};

class bad_gmean : public exception       // gmean的异常处理类 
{
private:
	double a;
	double b;
public:
	bad_gmean(double _a, double _b) : a(_a), b(-b) {}
	void mesg()
	{   
		cout << "gmean of " << a << " and " << b << " failed" << endl;
		cout << "function: gmean(), error: both of a and b should >=0" << endl;
	}
};

double hmean(double a, double b);
double gmean(double a, double b);

int main()
{
    double x, y, z;
    cout << "Enter two numbers: " << endl;
    while (cin >> x >> y)
    {
        try {                  // start of try block 
            z = hmean(x,y);
            cout << "Harmonic mean of " << x << " and " << y
                << " is " << z << endl;
            cout << "Geometric mean of " << x << " and " << y
                << " is " << gmean(x,y) << endl;
            cout << "Enter next set of numbers <q to quit>: ";
        }// end of try block
        catch (bad_hmean & bg)    // start of catch block
        {
            cout << bg.what() << endl;
            cout << "Try again.\n";
            break;
        }                  
        catch (bad_gmean & hg) 
        {
            cout << hg.what() << endl;
			cout << "you have no chance" << endl;
            break;
        } // end of catch block
    }
    cout << "Bye!\n";
    return 0;
}


double hmean(double a, double b)
{
    if (a == -b)      
	{
		// bad_hmean bh;
        throw bad_hmean(a,b);
	}
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0)
	{
		// bad_gmean bg;
        throw bad_gmean(a,b);
	}
    return sqrt(a * b); 
}

