#include <iostream>
#include <string>
#include <cstdio>
#include <valarray>

using namespace std;


class Student : private string, private valarray<double>
{
private : 
	typedef valarray<double>  ArrayDb;
	ostream& arr_out(ostream& os) const;
public:
	Student() : string("null student"), ArrayDb() {}
	explicit Student(const string &s) : string(s), ArrayDb() {}
	explicit Student(int n) : string("null student"), ArrayDb(n) {}
	Student(const string &s, int n) : string(s), ArrayDb(n) {}
	Student(const string &s, const ArrayDb &a) : string(s), ArrayDb(a) {}
	Student(const string &s, const double *pd, int n) : string(s), ArrayDb(pd, n) {}
	~Student() {}
	double Average() const;
	const string& Name() const;
	double& operator [](int i);          // 设置成绩
	double operator [](int i) const;    // 读取成绩
	
	// friends
	friend istream& operator  >>(istream& is, const Student &stu); // one word
	friend istream& getline(istream& is, const Student &stu);// one line
	friend ostream& operator <<(ostream& os, const  Student &stu);
};

double Student::Average() const 
{
	if(ArrayDb::size() > 0)
		return ArrayDb::sum()/ArrayDb::size();
	else
		return 0;
}

const string& Student::Name() const 
{
	return (const string &) *this;
}



double& Student::operator [](int i)
{
	return ArrayDb::operator [](i);
}


double Student::operator [](int i) const 
{
	return ArrayDb::operator [](i);
}

// private method 
ostream&  Student::arr_out(ostream &os)  const 
{
	int i;
	int lim = ArrayDb::size();
	if (lim > 0)
	{
		for (i=0; i<lim; i++)
		{
			os << ArrayDb::operator[](i) << " " << endl;
			if (i%5 == 4)
				os << endl;
		}
		if (i%5 != 0)
			os << endl;
	}
	else
		os << "empty array";
}


// friends
istream& operator >>(istream &is, Student &stu)
{
	is >> (string &)stu;
	return is;
}

istream& getline(istream &is, Student &stu)
{
	getline(is, (string &) stu);
	return is;
}

ostream& operator <<(ostream& os, const Student &stu)
{
	os << "scores for " << (const string &)stu << endl;
	stu.arr_out(os);
	return os;
}

void set(Student& sa, int n);
const int pupils = 3;
const int quizzes = 5;

int main()
{
	Student ada[pupils] = 
		{Student(quizzes), Student(quizzes), Student(quizzes)};
	
	for (int i = 0; i<pupils; i++)
		set(ada[i], quizzes);
	cout << endl << "student list: " << endl;
	for (int i=0; i<pupils; i++)
		cout << ada[i].Name() << endl;
	cout << endl << "result:";
	for(int i=0; i<pupils; i++)
	{
		cout << endl << ada[i];
		cout << "average: " << ada[i].Average() << endl;
	}
	cout << "Done." << endl;
	return 0;
}

void set(Student& sa, int n)
{
	cout << "please enter student's name : ";
	getline(cin, sa);
	cout << "please enter " << n << "quizzes" << endl;
	for (int i=0; i<n; i++)
	{
		cin >> sa[i];
	}
	while(cin.get() != '\n')
		continue;
}


