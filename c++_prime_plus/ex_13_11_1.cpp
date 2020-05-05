#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Cd
{
private:
	char performers[50];
	char label[20];
	int selections;
	double playtime; 
public:
	Cd(char *s1, char *s2, int n, double x)
	{
		strcpy(performers, s1);
		strcpy(label, s2);
		selections = n;
		playtime = x;
	}

	/* 
	Cd(const Cd &d)
	{
		strcpy(performers, d.performers);
		strcpy(label, d.label);
		selections = d.selections;
		playtime = d.playtime;
	}
	*/

	Cd()
	{
		strcpy(performers, "none");
		strcpy(label, "none");
		selections = 0;
		playtime = 0.0;
	}
	
	virtual ~Cd() {}  
	
	virtual void Report() const
	{
		cout << "performers: " << performers << endl;
		cout << "label: " << label << endl;
		cout << "selections: " << selections << endl;
		cout << "playtime: " << playtime << endl;
	}
	
	/*
	virtual Cd & operator=(const Cd &d) 
	{
		strcpy(performers, d.performers);
		strcpy(label, d.label);
		selections = d.selections;
		playtime = d.playtime;
	}
	*/
};


class Classic: public Cd
{
private:
	char art_works[100]; 
public:
	Classic(char *s1, char *s2, char *s3, int n, double x)
		: Cd(s1, s2, n, x) 
	{
		strcpy(art_works, s3);
	}
	
	Classic() : Cd() 
	{
		strcpy(art_works, "none");
	}

	virtual void Report() const 
	{
		cout << "art works:" << art_works << endl;
		Cd::Report();
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
	c2.Report();
	
	cout << "using type cd * pointer to objects" << endl;
	pcd->Report();
	pcd = &c2;
	pcd->Report();
	
	cout << "caling a cd reference argument" << endl;
	Bravo(c1);
	Bravo(c2);
	
	cout << "tesing assignment: ";
	Classic copy;
	copy = c2;
	copy.Report();
	
	system("pause");
	return 0;
}



void Bravo(const Cd &disk) 
{
	disk.Report();
}
