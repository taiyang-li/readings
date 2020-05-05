#include <iostream>
#include <string>
#include <cstdio>
#include <valarray>

using namespace std;



class Student
{
private : 
	typedef valarray<double>  ArrayDb;
	string name;
	ArrayDb scores;
	ostream & arr_out(ostream& os) const;
public:
	Student() : name("null student"), scores() {}
	explicit Student(const string &s) : name(s), scores() {}
	explicit Student(int n) : name("null student"), scores(n) {}
	Student(const string &s, int n) : name(s), scores(n) {}
	Student(const string &s, const ArrayDb &a) : name(s), scores(a) {}
	Student(const string &s, const double *pd, int n) : name(s), scores(pd, n) {}
	~Student() {}
	double Average() const;
	const string& Name() const;
	double& operator [](int i);          // 设置成绩
	double operator [](int i) const;    // 读取成绩
	
	// friends
	friend istream& operator  >>(istream& is, Student &stu); // one word
	friend istream& getline(istream& is, Student &stu);// one line
	friend ostream& operator <<(ostream& os, const Student &stu);
};

double Student::Average() const 
{
	if (scores.size() > 0)
		return scores.sum()/scores.size();
	else
		return 0;
}

const string& Student::Name() const
{
	return name;
}


double& Student::operator [](int i)
{
	return scores[i];
}

double Student::operator [](int i) const 
{
	return scores[i];
}

// private method
ostream& Student::arr_out(ostream& os) const
{
	int i;
	int lim = scores.size();
	if (lim > 0)
	{
		for (i=0; i<lim; i++)
		{
			os << scores[i] << " ";
			if (lim % 5 == 4) 
				os << endl;
		}
		if (i%5 != 0)
			os << endl; 
	}
	else
		os << "empty array" << endl;
	return os;
}

istream& operator>>(istream& is,  Student &stu)
{
	is >> stu.name;
	return is;
}

istream& getline(istream& is, Student &stu)
{
	getline(is, stu.name);
	return is;
}


ostream& operator<<(ostream& os, const Student& stu)
{
	os << "scrores for " << stu.Name() << endl;
	stu.arr_out(os);
	return os;
}

void set(Student &sa, int n);
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


void set(Student &sa, int n)
{
	cout << "please enter the student's name: ";
	getline(cin, sa);
	cout << "please enter " << n << " quiz scores:" << endl;
	for (int i=0; i<n; i++)
		cin >> sa[i];
	while (cin.get() != '\n')
		continue;
}






