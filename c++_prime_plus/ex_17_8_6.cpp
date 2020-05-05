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
	
	virtual void WriteAll(ostream &os)
	{
		os << "name: " << fname << " " << lname << endl; 
		os << "job: " << job << endl;  
	}
	
	virtual void GetAll(istream &is)
	{
		string temp;

		is >> temp;
		is >> fname;
		is >> lname;
		
		is >> temp;
		is >> job;  
	}
	
	friend ostream& operator <<(ostream &os, const abstr_emp &e)
	{	
		os << "name: " << e.fname << " " << e.lname << endl; 
		os << "job: " << e.job << endl;
		return os;
	}
	
	virtual ~abstr_emp() = 0;   
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
	virtual void WriteAll(ostream &os)
	{
		abstr_emp::WriteAll(os);
	}
	virtual void GetAll(istream &is)
	{
		abstr_emp::GetAll(is);
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
		abstr_emp::SetAll();
		cout << "enter inchargeof: ";
		cin >> InChargeOf();
	}
	virtual void WriteAll(ostream &os)
	{
		abstr_emp::WriteAll(os); 
		os << "in charge of: " << InChargeOf() << endl;
	}
	virtual void GetAll(istream &is)
	{
		abstr_emp::GetAll(is);
		
		string temp;
		for (int i=0; i<3; i++)
			is >> temp;
		is >> inchargeof;
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
	virtual void WriteAll(ostream &os)
	{
		abstr_emp::WriteAll(os); 
		os << "reportsto: " << ReportsTo() << endl;
	}
	virtual void GetAll(istream &is) 
	{
		abstr_emp::GetAll(is);
		string temp;
		is >> temp;
		is >> reportsto;
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
		cout << "warn" << endl;
	}
	
	virtual void WriteAll(ostream &os) 
	{
		abstr_emp::WriteAll(os);  
		os << "in charge of: " << InChargeOf() << endl; 
		os << "reportsto: " << ReportsTo() << endl;
	}
	virtual void GetAll(istream &is) 
	{
		abstr_emp::GetAll(is); 
		string temp; 

		for (int i=0; i<3; i++)
			is >> temp;
		is >> InChargeOf();
		
		is >> temp;
		is >> ReportsTo();
	}
};


const int MAX = 10;
bool is_first_run(string &file_name);  // 判断是否第一次运行 
void add_emp_menu(int cur_idx);  
abstr_emp* write_emp_to_file(int classtype, ostream &os);  
abstr_emp* read_emp_from_file(int classtype, istream &is);   
int main() 
{
	string file_name("emp.dat");
	abstr_emp *pc[MAX];
	int classtype;
	int emp_idx = 0;
		
	// 判断文件是否存在 
	if (is_first_run(file_name))
	{
		// 以只写方式打开
		ofstream fout(file_name);
		if (!fout.is_open())
			cout << "open file " << file_name << "failed" << endl;
		
		emp_idx = 0;  
		while (emp_idx < MAX)
		{
			add_emp_menu(emp_idx);
			cin >> classtype;
			if (classtype >= 4 || classtype <= -1)
			{
				cout << "classtype error" << endl;
				break;
			}
			fout << classtype << endl;   
			pc[emp_idx] = write_emp_to_file(classtype, fout);
			emp_idx++;
		}
		fout.close();

		// 释放所有申请内存 
		for (int i=0; i<emp_idx; i++)
			delete pc[i];
	}
	else
	{
		emp_idx = 0;

		// 首先读取文件 并 输出到屏幕 
		ifstream fin(file_name); 
		if (!fin.is_open())
			cout << "open file " << file_name << " failed" << endl;
		while (fin >> classtype)
		{
			pc[emp_idx] = read_emp_from_file(classtype, fin);
			emp_idx++;
		}
		for (int i=0; i<emp_idx; i++)
		{
			pc[i]->ShowAll();
			cout << endl;
		}
		fin.close();
		
		// 再增加employee 
		ofstream fout(file_name, ios::out | ios::app);
		if (!fout.is_open())
			cout << "open file " << file_name << " failed" << endl;
		while (emp_idx < MAX) 
		{
			add_emp_menu(emp_idx);
			cin >> classtype;
			if (classtype >= 4 || classtype <= -1)
			{
				cout << "classtype error" << endl;
				break;
			}
			fout << classtype << endl;
			pc[emp_idx] = write_emp_to_file(classtype, fout);
			emp_idx++;
		}
		// 释放内存
		for (int i=0; i<emp_idx; i++)
			delete pc[i];  	  
	} 
	system("pause");
	return 0;
}

bool is_first_run(string &file_name)
{
	ifstream  fin(file_name);
	if (!fin)
		return true;
	else
		return false;
} 

void add_emp_menu(int cur_idx) 
{
	cout << "------------ add the" << (cur_idx+1) << "-st employee ------------" << endl;
	cout << "--          0: employee  1: manager    --" << endl;
	cout << "--          2: fink      3: highfink   --" << endl;
	cout << "---------------------------------------------" << endl;
}

abstr_emp* write_emp_to_file(int classtype, ostream &os)    
{
	abstr_emp* res = nullptr;
	switch(classtype)
	{  
	case 0:
		res = new employee; break;
	case 1: 
		res = new manager;  break;
	case 2:
		res = new fink;     break;
	case 3:
		res = new highfink; break;
	default:
		return nullptr;  
	}
	res->SetAll();     
	res->WriteAll(os);
	return res;
} 

abstr_emp* read_emp_from_file(int classtype, istream &is) 
{
	abstr_emp* res = nullptr;
	switch(classtype)
	{  
	case 0:
		res = new employee; break;
	case 1: 
		res = new manager;  break;
	case 2:
		res = new fink;     break;
	case 3:
		res = new highfink; break;
	default:
		return nullptr;   
	}
	res->GetAll(is);  
	return res;
}









