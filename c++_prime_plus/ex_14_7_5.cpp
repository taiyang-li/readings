#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream> 
#include <cstring>
#include <cstdio>
#include <set> 

using namespace std;  	


class abstr_emp
{
private:
	string fname; 
	string lname; 
	string job;
public:
	abstr_emp() : fname("none"), lname("none"), job("none") {}   
	abstr_emp(const string &fn, const string &ln, const string &j)
		: fname(fn), lname(ln), job(j) {} 

	virtual void ShowAll() const
	{
		cout << "name: " << fname << " " << lname << endl;
		cout << "job: " << job << endl;
	}
	
	string get_fname() {return fname;}
	string get_lname() {return lname;}
	string get_job()  {return job;}
	
	virtual void SetAll()
	{
		cout << "enter first name: ";
		cin >> fname;
		cout << "enter last name: ";
		cin >> lname;
		cout << "enter job: ";
		cin >> job;
	}
	
	friend ostream& operator <<(ostream &os, const abstr_emp &e)
	{	
		os << "name: " << e.fname << " " << e.lname << endl; 
		os << "job: " << e.job << endl;
		return os;
	}

	virtual ~abstr_emp();  
};

abstr_emp::~abstr_emp() 
{
	cout << "destruction" << endl;
}



class employee : public abstr_emp
{
public:
	employee() : abstr_emp() {}
	employee(const string &fn, const string &ln, const string &j) 
		: abstr_emp(fn, ln, j) {}
	virtual void ShowAll() const
	{
		abstr_emp::ShowAll();
	}
	virtual void SetAll()
	{
		abstr_emp::SetAll();
	}
};

class manager : virtual public abstr_emp
{
private:
	int inchargeof;
protected:
	int InChargeOf() const {return inchargeof;}
	int& InChargeOf()  {return inchargeof;}
public:
	manager() : abstr_emp(), inchargeof(0) {}
	manager(const string &fn, const string &ln, const string &j, int ico=0)
		: abstr_emp(fn, ln, j), inchargeof(ico) {}
	manager(const abstr_emp &e, int ico)
		: abstr_emp(e), inchargeof(ico) {}
	manager(const manager &m)
		: abstr_emp(m), inchargeof(m.inchargeof) {}
	virtual void ShowAll() const
	{
		abstr_emp::ShowAll();
		cout << "in charge of: " << InChargeOf() << endl;
	}
	virtual void SetAll()
	{
		abstr_emp::ShowAll();
		cout << "enter inchargeof: ";
		cin >> InChargeOf();
	}
};

class fink : virtual public abstr_emp 
{
private:
	string  reportsto;
protected:	
	const string ReportsTo() const {return reportsto;}
	string& ReportsTo() {return reportsto;}
public:
	fink() : abstr_emp(), reportsto("none") {}
	fink(const string &fn, const string &ln, const string &j, const string &rpo)
		: abstr_emp(fn, ln, j), reportsto(rpo) {}
	fink(const abstr_emp &e, const string rpo)
		: abstr_emp(e), reportsto(rpo) {}
	fink(const fink &f)
		: abstr_emp(f), reportsto(f.reportsto) {}
	virtual void ShowAll() const
	{
		abstr_emp::ShowAll();
		cout << "reportsto: " << ReportsTo() << endl;
	}
	virtual void SetAll()
	{
		abstr_emp::SetAll();
		cout << "enter reportsto: ";
		cin >> ReportsTo();
	}
};

class highfink : public manager, public fink
{
public:
	highfink() : abstr_emp(), manager(), fink() {}
	highfink(const string &fn, const string &ln, const string &j, const string &rpo, int ico)
		: abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) {} 
	highfink(const abstr_emp &e, const string &rpo, int ico)
		: abstr_emp(e), manager(e, ico), fink(e, rpo) {}
	highfink(const manager &m, const string &rpo)
		: abstr_emp(m), manager(m), fink(m, rpo) {} 
	highfink(const fink &f, int ico)
		: abstr_emp(f), manager(f, ico), fink(f) {}
	highfink(const highfink &h)
		: abstr_emp(h), manager(h), fink(h) {} 
	
	virtual void ShowAll() const   
	{	
		abstr_emp::ShowAll();
		cout << "in charge of: " << InChargeOf() << endl;
		cout << "reportsto: " << ReportsTo() << endl;
		
	}
	
	virtual void SetAll()
	{
		abstr_emp::SetAll();
		cout << "enter inchargeof: ";
		cin >> InChargeOf(); 
		cout << "enter reportsto: ";
		cin >> ReportsTo();
	}
};

int main() 
{
	employee em("trip", "harris" , "thumper");
	// em.operator<<(cout);
	cout << em << endl;
	em.ShowAll();
	
	manager ma("amorphia", "spindragon", "nuancer", 5);
	// ma.operator<<(cout);
	ma.ShowAll();

	fink fi("matt", "oggs", "oliver", "juno barr");
	// fi.operator<<(cout);
	fi.ShowAll(); 
	
	highfink hf(ma, "curly Kew");
	hf.ShowAll();
	
	highfink hf2(hf);
	hf.ShowAll(); 

	cout << "using a abstr_emp *  pointer" << endl;
	abstr_emp tri[4] = {em, ma, hf, hf2};
	cout << endl;
	for (int i=0; i<4; i++)
	{
		tri[i].ShowAll(); 
		cout << endl;
	}
	
	system("pause");
	return 0;
}






