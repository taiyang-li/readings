#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class StringBad
{
private:
	char *str;  // 表示字符指针
	int len;    // 表示字符长度 
	static int num_strings; // 表示实例化对象个数
public:
	StringBad(const char *s);
	StringBad();
	~StringBad();
	// friend function
	friend ostream& operator << (ostream &os, const StringBad &str);
};

int StringBad::num_strings = 0;

void callme1(StringBad &);
void callme2(StringBad);

StringBad::StringBad(const char *s)
{
	len = strlen(s);
	str = new char(len+1);
	strcpy(str, s);
	num_strings++;
	cout << num_strings << ": " << str << endl;
}

StringBad::StringBad()
{
	len = 4;
	str = new char[4+1];
	strcpy(str, "C++");
	num_strings++;
	cout << num_strings << ": " << str << endl;
}

StringBad::~StringBad()
{
	cout << str << " deleted" << endl;
	--num_strings;
	cout << num_strings << " lefted" << endl;
	delete []str;
}

ostream& operator <<(ostream& os, const StringBad &st)
{
	os << st.str;
	return os;
}

int main()
{
	StringBad headline1("celery stalks at midnight");
	StringBad headline2("lettuce prey");
	StringBad sports("spinach leaves bowl for dollars");

	cout << "headline1: " << headline1 << endl;
	cout << "headline2: " << headline2 << endl;
	cout << "sports: " << sports << endl;

	callme1(headline1);
	cout << "headline1: " << headline1 << endl;
	
	callme1(headline2);
	cout << "headline2: " << headline2 << endl;
	
	StringBad sailor = sports;
	cout << "sailor: " << sports << endl;
	StringBad knot;
	knot = headline1;
	cout << "knot: " << knot << endl;
	
	return 0;

}


void callme1(StringBad &rsb)
{
	cout << "String passed by reference" << endl;
	cout << rsb << endl;
}


void callme2(StringBad sb)
{
	cout << "String passed by value" << endl;
	cout << sb << endl;
}




