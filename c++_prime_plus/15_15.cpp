#include <cstdio>
#include <new>
#include <string>
#include <iostream> 

using namespace std; 

class Sales
{
public:
	enum {MONTHS = 12};
	class bad_index : public logic_error
	{
	private:
		int bi; // bad index
	public:
		explicit bad_index(int ix, const string &s = "index error in sales object\n");
		int bi_val() const {return bi;}
		virtual ~bad_index() throw() {}  
	};

	explicit Sales(int yy=0);
	Sales(int yy, const double *gr, int n);
	virtual ~Sales() {}
	int Year() const {return year;}
	virtual double operator [](int i) const;
	virtual double& operator [](int i);
private:
	double gross[MONTHS];
	int year;
};

class LabeledSales: public Sales
{
public:
	class nbad_index: public Sales::bad_index
	{
	private:
		string lb1;
	public:
		nbad_index(const string &lb, int ix, const string &s="index error in labelsales object\n");
		const string& label_val() const  {return lb1;}
		virtual ~nbad_index() throw() {}
	};
	explicit LabeledSales(const string &lb = "none", int yy = 0);
	LabeledSales(const string lb, int yy, const double *gr, int n);
	virtual ~LabeledSales() {} 
	const string& Label() const {return label;}
	virtual double operator [](int i ) const ;
	virtual double& operator [](int i);
private:
	string label; 
};



Sales::bad_index::bad_index(int ix, const string &s): logic_error(s), bi(ix) {}

Sales::Sales(int yy)
{
	year = yy;
	for (int i=0; i<MONTHS; i++)
		gross[i] = 0;
}

Sales::Sales(int yy, const double *gr, int n)
{
	year = yy;	
	int lim = n<MONTHS ? n : MONTHS;
	int i;
	for (i=0; i<lim; i++)
		gross[i] = gr[i];
	for (; i<MONTHS; i++)
		gross[i] = 0;
}

double Sales::operator [](int i) const 
{
	if (i<0 || i>=MONTHS) 
		throw bad_index(i);
	return gross[i];
}

double& Sales::operator [](int i)
{
	if (i<0 || i>=MONTHS) 
		throw bad_index(i);
	return gross[i];
}


LabeledSales::nbad_index::nbad_index(const string &lb, int ix, const string &s): lb1(lb), bad_index(ix, s) {}


LabeledSales::LabeledSales(const string &lb, int yy) : label(lb), Sales(yy) {}

LabeledSales::LabeledSales(const string lb, int yy, const double *gr, int n)
	: Sales(yy, gr, n), label(lb) {}


double LabeledSales::operator [](int i) const
{	
	if (i<0 || i>MONTHS)
		throw nbad_index(Label(), i);  
	return Sales::operator[](i); 
}

double& LabeledSales::operator [](int i)
{
	if (i<0 || i>MONTHS)
		throw nbad_index(Label(), i);  
	return Sales::operator[](i); 	
}



int main()
{
	double vals1[12] = 
	{
		1220, 1100, 1122, 2212, 1232, 2334, 
		2884, 2393, 3302, 2932, 3002, 3544
	};

	double vals2[12] = 
	{
		21, 11, 22, 21, 32, 23,
		28, 29, 33, 29, 32, 35
	};
	
	Sales sales1(2011, vals1, 12);
	LabeledSales sales2("BlogStar", 2012, vals2, 12);
	
	cout << "first try block" << endl;
	
	try 
	{
		int i;
		
		cout << "year = " << sales1.Year() << endl;
		for (i=0; i<12; i++)
		{
			cout << sales1[i] << "\t" << endl;
			if (i%6 == 5)
				cout << endl;
		}

		cout << "label = " << sales2.Label() << endl;
		cout << "year = " << sales2.Year() << endl;
		for (i=0; i<12; i++)
		{
			cout << sales2[i] << endl;
			if (i%6 == 5)
				cout << endl;
		}
	}
	catch (LabeledSales::nbad_index &bad)
	{
		cout << bad.what() << endl;
		cout << "company = " << bad.label_val() << endl;
		cout << "bad index = " << bad.bi_val() << endl;
	}
	catch (Sales::bad_index &bad)
	{
		cout << bad.what() << endl;
		cout << "bad index = " << bad.bi_val() << endl;
	}

	cout << endl << "next try block" << endl;
	try 
	{
		sales2[2] = 37.5;
		sales1[20] = 1335;
		cout << "entry of try block 2" << endl;
	}
	catch (LabeledSales::nbad_index &bad)
	{
		cout << bad.what() << endl;
		cout << "company = " << bad.label_val() << endl;
		cout << "bad index = " << bad.bi_val() << endl;
	}
	catch (Sales::bad_index &bad)
	{
		cout << bad.what() << endl;
		cout << "bad index = " << bad.bi_val() << endl;
	}
	
	cout << "Done" << endl;
	system("pause");
	return 0;
}


