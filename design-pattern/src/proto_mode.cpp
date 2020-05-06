#include <iostream>
#include <cstring>
using namespace std;

class Resume
{
	protected:
		char* _name;

		virtual void SetPersonalInfo() {}
		virtual void SetEducation() {}
		virtual void SetWorkExp() {}

	public:
		Resume() {}
		virtual ~Resume() {}
		virtual Resume* clone() {return NULL;}
		virtual void set(const char* n) {}
		virtual void show() {}

		void FillResume()
		{
			SetPersonalInfo();
			SetEducation();
			SetWorkExp();
		}
};

class ResumeA : public Resume
{
	public:
		ResumeA(const char* str);
		ResumeA(const ResumeA& r);
		~ResumeA();

		ResumeA* clone();
		void show();

		virtual void SetPersonalInfo()
		{
			cout << " set personal infomation" << endl;
		}

		virtual void SetEducation()
		{
			cout << "set education" << endl;
		}

		virtual void SetWorkExp()
		{
			cout << "set work experience" << endl;
		}
};

ResumeA::ResumeA(const char* str)
{
	if (str == NULL)
	{
		_name = new char[1];
		*_name = '\0'; 
	}
	else
	{
		_name = new char[strlen(str)+1];
		strcpy(_name, str);
	}
}

ResumeA::ResumeA(const ResumeA& r)
{
	if (r._name == NULL)
	{
		_name = new char[1];
		*_name = '\0';
	}
	else
	{
		_name = new char[strlen(r._name)+1];
		strcpy(_name, r._name);
	}
}

ResumeA::~ResumeA()
{
	if (_name != NULL)
	{
		delete[] _name;
	}
}

ResumeA* ResumeA::clone()
{
	cout << "hello" << endl;
	return new ResumeA(*this);
}

void ResumeA::show()
{
	cout << "name: " <<  _name << endl;
}

int main()
{
	ResumeA *r1 = new ResumeA("A");
	r1->show();
	ResumeA *r2 = r1->clone();
	delete r1;

	r2->show();
	r2->FillResume();

	return 0;
}


