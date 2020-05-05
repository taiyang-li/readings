#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Cd
{
private:
	char *performers;  // 50
	char *label;       // 20 
	int selections;        
	double playtime; 
public:
	
	Cd(char *s1, char *s2, int n, double x)
	{
		performers = new char[strlen(s1) + 1];
		label = new char[strlen(s2) + 1];
		 
		strcpy(performers, s1);
		strcpy(label, s2);
		selections = n;
		playtime = x;
	}

	
	Cd(const Cd &d)
	{
		performers = new char[strlen(d.performers) + 1];
		label = new char[strlen(d.label) + 1];
		
		strcpy(performers, d.performers);
		strcpy(label, d.label);
		selections = d.selections;
		playtime = d.playtime;
	}
	

	Cd()
	{
		performers = new char[50];
		label = new char[20];

		strcpy(performers, "none");
		strcpy(label, "none");
		selections = 0;
		playtime = 0.0;
	}
	
	virtual ~Cd() { 
		delete [] performers;
		delete [] label;
	}  
	
	virtual void Report() const
	{
		cout << "performers: " << performers << endl;
		cout << "label: " << label << endl;
		cout << "selections: " << selections << endl;
		cout << "playtime: " << playtime << endl;
	}
	
	
	virtual Cd & operator=(const Cd &d) 
	{
		if (this == &d)
			return *this;

		delete [] performers;
		delete [] label;
		performers = new char[strlen(d.performers) + 1];
		label = new char[strlen(d.label) + 1];
		
		strcpy(performers, d.performers);
		strcpy(label, d.label);
		selections = d.selections;
		playtime = d.playtime;
		return *this;
	}
};


class Classic: public Cd
{
private:
	char *art_works; // 100 
public:
	Classic(char *s1, char *s2, char *s3, int n, double x)
		: Cd(s1, s2, n, x) 
	{
		art_works = new char[strlen(s3) + 1]; 
		strcpy(art_works, s3);
	}

	Classic(const Classic &cla) : Cd(cla)
	{
		art_works = new char[strlen(cla.art_works) + 1];
		strcpy(art_works, cla.art_works);
	}
	
	Classic() : Cd() 
	{
		art_works = new char[100]; 
		strcpy(art_works, "none");
	}

	virtual ~Classic() { 
		delete [] art_works;
	}
	
	virtual void Report() const 
	{
		cout << "art works:" << art_works << endl;
		Cd::Report();
	}

	virtual Classic& operator=(const Classic &d) 
	{
		Cd::operator=(d);
		delete [] art_works;
		art_works = new char[strlen(d.art_works) + 1];
		strcpy(art_works, d.art_works);
		return *this;
	}
};



void Bravo(const Cd &disk);


int main()
{
	Cd c1("Beatles", "Capitol", 14, 35.5);
	Classic c2 = Classic("Piano sonata in B flat, Fantasia in C", "alfred brendel", "philips", 2, 57.17);
	
	Cd *pcd = &c1;

	cout << "using object directly" << endl;
	c1.Report();
	cout << endl;
	
	c2.Report();
	cout << endl;

	
	cout << "using type cd * pointer to objects" << endl;
	pcd->Report();
	cout << endl;
	pcd = &c2;
	pcd->Report();
	cout << endl;
	
	cout << "caling a cd reference argument" << endl;
	Bravo(c1);
	cout << endl;
	Bravo(c2);
	cout << endl;
	
	cout << "tesing assignment: ";
	Classic copy;
	copy = c2;
	copy.Report();
	cout << endl;
	
	system("pause");
	return 0;
}



void Bravo(const Cd &disk) 
{
	disk.Report();
}
