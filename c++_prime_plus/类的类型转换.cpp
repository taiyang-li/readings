#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;



class Stonewt
{
private:
	enum {Lbs_per_stn = 14};
	int stone;             
	double pds_left;
	double pounds;
public:
	Stonewt(double lbs);
	Stonewt(int stn, double lbs);
	Stonewt();
	~Stonewt();
	void show_lbs() const;
	void show_stn() const;
	
	// conversion function 
	operator int() const;
	operator double() const;
};

Stonewt::Stonewt(double lbs)
{
	stone = int(lbs) / Lbs_per_stn;
	pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
	pounds = lbs;
}

Stonewt::Stonewt(int stn, double lbs)
{
	stone = stn;
	pds_left = lbs;
	pounds = stn * Lbs_per_stn + lbs;
}

Stonewt::Stonewt()
{
	stone = 0;
	pounds = 0;
	pds_left = 0;
}

Stonewt::~Stonewt()
{
	;
}

void Stonewt::show_stn() const 
{
	cout << stone << " Stone, " << pds_left << " pounds" << endl;
}

void Stonewt::show_lbs() const
{
	cout << pounds << " pounds" << endl;
}


void display(const Stonewt &st, int n);

int main()
{
	Stonewt incognito = 275;
	Stonewt wolfe(285.7);
	Stonewt taft(21, 8);
	
	incognito.show_stn();
	wolfe.show_stn();
	taft.show_lbs();
	
	incognito = 276.8;
	taft = 325;
	
	incognito.show_stn();
	taft.show_lbs();
	display(taft,2);
	display(422,2);

	// test conversion functions
	Stonewt poppins(9, 2.8);
	double p_wt = poppins;   // 隐式转换
	cout << p_wt << " pounds" << endl;
	cout << int(poppins) << " pounds" << endl;
	
	

	system("pause");
	return 0;
}


void display(const Stonewt &st, int n)
{
	for (int i=0; i<n; i++)
	{
		cout << "Wow " ;
		st.show_stn();
	}
}


Stonewt::operator int() const
{
	return int(pounds + 0.5);
}

Stonewt::operator double() const
{
	return pounds;
}







