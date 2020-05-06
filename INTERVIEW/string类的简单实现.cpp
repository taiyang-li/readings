#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class my_string
{
public:
	my_string();                        // 默认构造函数 
	my_string(const char *str);  // 普通构造函数
	my_string(const my_string &other);  // 拷贝构造函数
	~my_string(void);					// 析构函数
	my_string& operator=(const my_string &other); // 赋值函数
	void print_string(void);
private:
	char *m_data;
};


my_string::my_string() 
{
	m_data = new char[1];
	m_data = '\0';
}

my_string::my_string(const char *str)
{	
	if (str == NULL)
	{
		m_data = new char[1];
		*m_data = '\0';
	}
	else
	{
		int len = strlen(str);
		m_data = new char[len+1];
		strcpy(m_data, str);
	}
}

my_string::~my_string(void)
{
	delete m_data;
}


my_string::my_string(const my_string &other)
{	
	if (other.m_data == NULL)
	{
		m_data = new char[1];
		*m_data = '\0';
	}
	else
	{
		int len = strlen(other.m_data);
		m_data = new char[len+1];
		strcpy(m_data, other.m_data);
	}
}

my_string&  my_string::operator =(const my_string &other)
{	
	if (this == &other)  // 若占用同一块内存，不做任何改变
		return *this;
	
	// 如果不是
	delete m_data;
	int len = strlen(other.m_data);
	m_data = new char[len+1];
	strcpy(m_data, other.m_data);
	return *this;
}

void my_string::print_string(void)
{
	cout << m_data << endl;
}

int main()
{
	my_string a("i am a string");
	my_string b(a);
	my_string c;
	c = a;

	cout << "a: "; a.print_string();	
	cout << "b: "; b.print_string();
	cout << "c: "; c.print_string();
	
	getchar();
	return 0;
}
