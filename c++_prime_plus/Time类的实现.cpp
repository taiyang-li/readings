#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Time
{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m=0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h=0, int m=0);
	Time Sum(const Time &t) const;  // 求时间和
	void Show() const;
};

Time::Time()
{
	hours = 0;
	minutes = 0;
}

Time::Time(int h, int m)
{
	hours = h;
	minutes = m;
}

void Time::AddMin(int m)
{	
	minutes += m;
	hours += minutes/60;
	minutes %= 60;
}
void Time::AddHr(int h)
{
	hours += h;
}

void Time::Reset(int h, int m)
{
	hours = h;
	minutes = m;
}

Time Time::Sum(const Time &t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes/60;
	sum.minutes %= 60;
	return sum;
}

void Time::Show() const 
{
	cout << hours << ": " << minutes << endl;
}


int main()
{
	Time planning;
	Time coding(2,40);
	Time fixing(5,55);
	Time total;

	planning.Show();
	coding.Show();
	fixing.Show();
	

	total = coding.Sum(fixing);
	total.Show();
	

	system("pause");
	return 0;
}


