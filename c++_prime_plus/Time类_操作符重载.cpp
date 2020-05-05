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
	Time operator +(const Time &t) const;
	Time operator -(const Time &t) const;
	Time operator *(double n) const;

	friend Time operator *(double m, const Time &t);
	friend ostream& operator <<(ostream &os, const Time &t);
	
};

// 注意 输入流和输出流都是引用形式
ostream& operator <<(ostream &os, const Time &t)
{
	os << t.hours << ": " << t.minutes << endl;
	return os;
}


Time operator *(double m, const Time &t)
{
	Time res;
	long total = (t.hours * 60 + t.minutes) * m;
	res.hours = total/60;
	res.minutes = total%60;
	return res;
}


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


Time Time::operator +(const Time &t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes/60;
	sum.minutes %= 60;
	return sum;
}

Time Time::operator -(const Time &t) const
{
	Time diff;
	int tot1;
	int tot2;
	tot1 = minutes + 60 * hours;
	tot2 = t.minutes + 60 * t.hours;
	diff.minutes = (tot1 - tot2)%60;
	diff.hours = (tot1 - tot2)/60;
	return diff;
}

Time Time::operator *(double n) const
{
	Time res;
	int tot = minutes + 60*hours;
	tot *= n;
	res.hours = tot/60;
	res.minutes = tot%60;
	return res;
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

	total = coding + fixing + planning;
	total.Show();

	total= fixing - coding;
	total.Show();
	
	total = coding * 2;
	total.Show();

	cout << total << coding << fixing;


	system("pause");
	return 0;
}






