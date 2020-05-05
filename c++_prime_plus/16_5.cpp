#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>

using namespace std;


class Report
{
public:
	Report(const string &s):str(s) {cout << "object created" << endl;}
	~Report()  {cout << "obeject deleted!" << endl;}
	void comment() const {cout << str << endl;}
private:
	string str;
};



int main()
{
	{
		auto_ptr<Report> ps(new Report("using auto_ptr"));
		ps->comment();
	}
	{
		shared_ptr<Report> ps(new Report("using auto_ptr"));
		ps->comment();
	}
	{
		unique_ptr<Report> ps(new Report("using auto_ptr"));
		ps->comment();
	}
	system("pause");
	return 0;
}
