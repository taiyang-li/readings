#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio> 

using namespace std;

class ABC  
{
private:
	char *label;
	int rating;
protected:	 
	char* Label() const  {return label;}  
	char*& Label() {return label;}
	int Rating() const  {return rating;}   
	int& Rating() {return rating;} 
public:
	ABC(const char *l = "null", int r = 0) 
	{
		label = new char[strlen(l) + 1];
		strcpy(label, l);
		rating = r;
	}
	
	virtual ~ABC()
	{
		delete [] label; 
	}

	virtual void Show() = 0; 

	virtual ABC& operator=(const ABC &a)
	{
		if (&a == this)
			return *this;
		delete [] label;
		label = new char(strlen(a.label)+1);
		rating = a.rating; 
		return *this;
	}
	

	friend ostream & operator<<(ostream & os, const ABC & rs)
	{
		os << "label: " << rs.label << endl;
		os << "rating: " << rs.rating << endl;
		return os;  
	}		
};

void ABC::Show()
{
	cout << "label: " << label << endl;
	cout << "rating: " << rating << endl;
}

class baseDMA : public ABC
{
public:
    baseDMA(const char * l = "null", int r = 0)
		: ABC(l, r) {}
   
	virtual ~baseDMA() {}            // test if ~ABC() is needed  

	virtual void Show()
	{
		// ABC::Show();
		cout << *this;
	}

    baseDMA & operator=(const baseDMA & rs)
	{
		ABC::operator=(rs);
	}

    friend ostream & operator<<(ostream & os, 
                                     const baseDMA & rs)
	{
		os << (ABC &) rs;  
		return os;
	}		
};


class lacksDMA : public ABC
{
private:
    enum { COL_LEN = 40};
    char color[COL_LEN];
public:
    lacksDMA(const char * c = "blank", const char * l = "null", int r = 0)
		: ABC(l, r)
	{
		strcpy(color, c);
	}

	virtual ~lacksDMA() {}

	virtual void Show()
	{
		// ABC::Show();
		// cout << "color: " << color << endl; 
		cout << *this;
	}
	
    friend ostream & operator<<(ostream & os, const lacksDMA & rs)
	{
		os << (ABC &)rs;
		os << "color: " << rs.color << endl; 
		return os;
	}
};


class hasDMA :public ABC
{
private:
    char * style;
public:
    hasDMA(const char * s = "none", const char * l = "null", int r = 0)
		: ABC(l, r)
	{
		
		style = new char[strlen(s) + 1];
		strcpy(style, s);
	}
	
    ~hasDMA()
	{
		delete [] style;
	}

	virtual void Show()
	{
		// ABC::Show();
		// cout << "style: " << style << endl;  
		cout << *this;
	}

    hasDMA & operator=(const hasDMA & rs)
	{
		if (&rs == this)
			return *this;
		ABC::operator=(rs);
		delete [] style;
		style = new char[strlen(rs.style) + 1];
		strcpy(style, rs.style);
		return *this;
	}
	
    friend ostream & operator<<(ostream & os,  
                                     const hasDMA & rs)
	{
		os << (ABC &)rs;
		os << "style: " << rs.style << endl;
		return os;
	}
};

const int DMAS = 3;
int main()
{
	ABC *p_dma[DMAS]; 
	char label[30];
	int rating;
	int kind;
	char color[40];
	char style[30];
	
	for (int i=0; i<DMAS; i++)
	{
		cout << "enter the label: " << endl;
		cin >> label;
		cout << "enter the rating: " <<endl;
		cin >> rating;
		
		cout << "enter 1 for baseDMA. 2 for lacksDMA, 3 for hasDMA" << endl;
		cin >> kind;
		switch(kind)
		{
		case 1:
			p_dma[i] = new baseDMA(label, rating);
			break;
		case 2:
			cout << "enter the color: " << endl;
			cin >> color;
			p_dma[i] = new lacksDMA(color, label, rating); 
			break;
		case 3:
			cout << "enter the style: " << endl; 
			cin >> style;
			p_dma[i] = new hasDMA(style, label, rating);
			break;
		default:
			cout << "input kind error" << endl;
		}
		p_dma[i]->Show();
	}
	system("pause");
	return 0;
}

