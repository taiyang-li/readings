#include <cstring>
#include <iostream>
#include <cstdlib>


using namespace std;


class String
{
private:
	char *str;
	int len;
	static int num_strings;
	static const int CINLIM = 80;
public:
	// constructors
	String(const char *s);
	String();
	String(const String &);
	~String();
	
	int length() const  {return len;}
	
	// overload operator methods 
	String& operator =(const String &);
	String& operator =(const char *);
	char& operator [](int i);
	const char& operator[](int i) const;
	
	// overload operator friends
	friend bool operator >(const String &st1, const String &st2);
	friend bool operator <(const String &st1, const String &st2);
	friend bool operator ==(const String &st1, const String &st2);
	friend ostream& operator<<(ostream &os, const String &st);
	friend istream& operator>>(istream &is, String &st);
	
	// static function 
	static int HowMany();
};


int String::num_strings = 0;



int String::HowMany()
{
	return num_strings;
}

String::String(const char *s)
{	
	len = strlen(s);
	str = new char[len+1];
	strcpy(str, s);
	num_strings++;
}


String::String()
{
	len = 1;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

String::String(const String &st)
{
	len = st.len;
	str = new char[len+1];
	strcpy(str, st.str);
	num_strings++;
}

String::~String()
{
	--num_strings;
	delete []str;
}

String& String::operator =(const String &st)
{
	if (this == &st)
		return *this;
	
	delete []str;
	len = st.len;
	str = new char[len+1];
	strcpy(str, st.str);
}


String& String::operator =(const char *s)
{
	delete []str;
	len = strlen(s);
	str = new char[len+1];
	strcpy(str, s);
	return *this;
}
 
// write
char& String::operator [](int i)
{
	return str[i];
}

// read 
const char& String::operator [](int i) const
{	
	return str[i];
}

bool operator <(const String &st1, const String &st2)
{	
	return  strcmp(st1.str, st2.str)<0;
}

bool operator >(const String &st1, const String &st2)
{
	return strcmp(st1.str, st2.str) > 0;
}

bool operator ==(const String &st1, const String &st2)
{
	return strcmp(st1.str, st2.str) == 0;
}

ostream& operator <<(ostream &os, const String &st)
{
	os << st.str;
	return os;
}

istream& operator >>(istream &is, String &st)
{	
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is)
		st = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}


const int ArSize = 10;
const int MaxLen = 81;
int main()
{
	cout << "what is your name: " << endl;
	String sayings[ArSize];
	char temp[MaxLen];
	int i;
	for (i=0; i<ArSize; i++)
	{
		cout << i+1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')
			break;
		else
			sayings[i] = temp;
	}
	
	int total = i;
	
	if (total > 0)
	{
		cout << "here are your saying" << endl;
		for (int i=0; i<total; i++)
			cout << sayings[i][0] << ": " << sayings[i] << endl;
		cout << "ok!" << endl;

		String *shortest = &sayings[0];
		String *first = &sayings[0];
		for (i=1; i<total; i++)
		{
			if (sayings[i].length() < shortest->length())
				shortest = &sayings[i];
			if (sayings[i] < *first)
				first = &sayings[i];
		}

		cout << "shortest: " << *shortest << endl;
		cout << "first: " <<  *first << endl;
		cout << endl;
		
		/*
		int shortest = 0;
		int first = 0;
		for (i=1; i<total; i++)
		{
			if (sayings[i].length() < sayings[shortest].length())
				shortest = i;
			if (sayings[i] < sayings[first])
				first = i;
		}

		cout << "shortest saying: " << endl;
		cout << sayings[shortest] << endl;
		cout << "first alphabetically" << endl;
		cout << sayings[first] << endl;
		cout << "this program used " << String::HowMany() 
			<< " string objects. Bye " << endl;;
		*/
	}
	else
		cout << "no input. Bye " << endl;
	
	

}




