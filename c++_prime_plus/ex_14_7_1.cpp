#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <valarray>
#include <iomanip>

using namespace std;

template <class T1, class T2>
class Pair
{
private:
    T1 a;
    T2 b;
public:
    T1 & first();     
    T2 & second();
	T1 first() const { return a; }
    T2 second() const { return b; }
    Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { }
    Pair() {}
};

template<class T1, class T2>
T1 & Pair<T1,T2>::first()
{
    return a;
}
template<class T1, class T2>
T2 & Pair<T1,T2>::second()
{
    return b;
}


class Wine
{
private:
	typedef valarray<int> ArrayInt; 
	typedef Pair<ArrayInt, ArrayInt> PairArray;   

	string label;
	PairArray yr_bot;
	int year_no;

public:
	Wine(const char *l, int y, const int yr[], const int bot[]) : label(l), year_no(y)
	{
		ArrayInt  year(yr, y);
		ArrayInt  bottles(bot, y);
		yr_bot.first() = year;
		yr_bot.second() = bottles; 
	}
	Wine(const char *l, int y) : label(l), year_no(y), yr_bot(valarray<int>(y), valarray<int>(y)) {}
	void GetBottles();
	void Show();
	string& Label();
	int sum();	 
};



void Wine::GetBottles()
{
	for (int i=0; i<year_no; i++)
	{
		cout << "enter year: " << endl;
		cin >> yr_bot.first()[i];  
		cout << "enter the bottles of that year: " << endl;
		cin >> yr_bot.second()[i];
	}
}

void Wine::Show()
{
	cout << "Wine: " << label << endl;
	cout << "\t\t";
	cout << setw(8) << left << "year";
	cout << setw(10) << left << "bottles" << endl;
	
	for (int i=0; i<year_no; i++)
	{
		cout << "\t\t";
		cout << setw(8) << left << yr_bot.first()[i];
		cout << setw(10) << left << yr_bot.second()[i] << endl;
	}
}


string& Wine::Label()
{
	return label;
}

int Wine::sum()  
{
	return yr_bot.second().sum();
}


int main(void)
{
	cout << "enter name of Wine: " << endl;
	char lab[50];
	cin.getline(lab, 50);
	cout << "enter number of years: " << endl;
	int yrs;
	cin >> yrs;
	
	Wine holding(lab, yrs); 
	holding.GetBottles();
	holding.Show();

	const int YRS = 3;
	int y[YRS] = {1993, 1995, 1998};
	int b[YRS] = {48, 60, 72};
	
	Wine more("gushing grape red", YRS, y, b);
	more.Show();
	cout << "total bottles for " << more.Label() 
		 << ": " << more.sum() << endl;
	cout << "Bye" << endl;
	system("pause");
	return 0;
}
