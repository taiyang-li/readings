#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

class baseDMA
{
private:
	char *label;
	int rating;
public:
	baseDMA(const char *l = "null", int r = 0);
	baseDMA(const baseDMA &rs);
	virtual ~baseDMA();
	baseDMA& operator=(const baseDMA &rs);
	friend ostream & operator<<(ostream &os, const baseDMA &rs);		
};


class lacksDMA: public baseDMA
{
private:
	enum {COL_LEN = 40};
	char color[COL_LEN];   // COLOR
public:
	lacksDMA(const char *c = "blank", const char *l = "null", int r = 0);
	lacksDMA(const char *c , const baseDMA &rs);
	friend ostream& operator <<(ostream &os, const lacksDMA &rs);
};

class hasDMA: public baseDMA
{
private:
	char *style;
public:
	hasDMA(const char *s = "none", const char *l = "null", int r = 0);
	hasDMA(const char *s, const baseDMA &rs);
	hasDMA(const hasDMA &hs);
	~hasDMA();
	hasDMA &operator=(const hasDMA &rs);
	friend ostream& operator<<(ostream &os, const hasDMA &rs);

};


baseDMA::baseDMA(const char *l, int r)
{
	label = new char[strlen(l)+1];
	strcpy(label, l);
	rating = r;
}
	


baseDMA::baseDMA(const baseDMA &rs)
{
	label = new char(strlen(rs.label) + 1);
	strcpy(label, rs.label);
	rating = rs.rating;
}


baseDMA::~baseDMA()
{
	delete [] label;
}

baseDMA& baseDMA::operator =(const baseDMA &rs)
{
	if (this == &rs)
		return *this;
	delete []  label;
	label = new char[strlen(rs.label)+1];
	strcpy(label, rs.label);
	rating = rs.rating;
	return *this;
}


ostream& operator <<(ostream &os, const baseDMA &rs)
{
	os << "label: " << rs.label << endl;
	os << "rating: " << rs.rating << endl;
	return os;
}



// lacksDMA methods
lacksDMA::lacksDMA(const char *c, const char *l, int r) : baseDMA(l, r)
{
	strncpy(color, c, 39);
	color[39] = '\0';
}


lacksDMA::lacksDMA(const char *c, const baseDMA &rs) : baseDMA(rs)
{
	strncpy(color, c, 39);
	color[39] = '\0';
}

ostream& operator <<(ostream &os, const lacksDMA &ls)
{
	os << (const baseDMA&) ls;
	os << "color: " << ls.color << endl;
	return os;
}


// hasDMA methods
hasDMA::hasDMA(const char *s, const char *l, int r) : baseDMA(l, r)
{
	style = new char[strlen(s) + 1];
	strcpy(style, s);
}

hasDMA::hasDMA(const char *s, const baseDMA &rs) : baseDMA(rs)
{
	style = new char[strlen(s) + 1];
	strcpy(style, s);
}

hasDMA::hasDMA(const hasDMA &hs) : baseDMA(hs)
{
	style = new char[strlen(hs.style) + 1];
	strcpy(style, hs.style);
}

hasDMA::~hasDMA()
{
	delete [] style;
}

hasDMA& hasDMA::operator =(const hasDMA &hs)
{
	if (this == &hs)
		return *this;
	baseDMA::operator =(hs);
	delete [] style;
	style = new char [strlen(hs.style) + 1];
	strcpy(style, hs.style);
	return *this;
}

ostream& operator <<(ostream &os, const hasDMA &hs)
{
	os << (const baseDMA &)hs;
	os << "style: " << hs.style << endl;
	return os;
}

int main()
{
	baseDMA shirt("protabelly", 8);
	lacksDMA ballon("red", "blimpo", 4);
	hasDMA map("mercator", "buffalo keys", 5);

	cout << "display baseDMA object: " << endl;
	cout << shirt << endl;
	cout << endl;

	cout << "display lacksDMA object:" << endl;
	cout << ballon << endl;
	cout << endl;
	
	cout << "display hasDMA object: " << endl;
	cout << map << endl;
	cout << endl;

	lacksDMA ballon2(ballon);
	cout << "result of lacksDMA copy:" << endl;
	cout << ballon2 << endl;
	
	hasDMA map2;
	map2 = map;
	cout << "result of hasDMA assignment" << endl;
	cout << map2 << endl;
	return 0;	
}

