#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

string str[22];
string commend;
int N;
inline string MyCopy();	// copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
inline string MyAdd();	// add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
inline int MyFind();	// find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
inline int MyRfind();	// rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
inline void MyInsert();	// insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
inline void MyReset();	// reset S N：将第N个字符串变为S。
struct GETS
{
GETS(string &s)	// 递归获得真正的s串
{
cin >> s;
if (s=="copy")
s = MyCopy();
else if (s=="add")
s = MyAdd();
}
};

struct GETINT
{
string Commend;
GETINT(int &n)	// 递归获得真正的int n
{
cin >> Commend;
if (Commend=="find")
n = MyFind();
else if (Commend=="rfind")
n = MyRfind();
else
n = atoi(Commend.c_str());
}
};

struct GETSTRING
{
GETSTRING(int &m, string &s)	// 递归获得真正的s串 并判断其是否为整数
{
GETS Gets(s);
int i = 0;
for (m=0; i<s.length(); i++)
if ((s.at(i)>='0')&&(s.at(i)<='9'))
m = m * 10 + s.at(i)-'0';
else
break;
if ((i!=s.length())||(m>99999))
m = -1;
}
};

int main()
{
cin >> N;
for (int i=0; i<N; i++)
cin >> str[i+1];
while (cin >> commend)
{
if (commend=="over")
break;
switch(commend.at(1))
{
case 'n':	MyInsert(); break;
case 'e':	MyReset(); break;
case 'r':	if (commend=="print")
{
int n;
cin >> n;
cout << str[n] << endl;
}
else 
{
for (int j=1; j<=N; j++)
cout << str[j] << endl;
}
break;
}
}
return 0;
}

inline string MyCopy()
{
int n, x, l;
GETINT getintn(n);
GETINT getintx(x);
GETINT getintl(l);
return (str[n].substr(x,l));
}

inline string MyAdd()	// add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
{
string s1,s2;
int m=-1, n=-1;
GETSTRING getstringms1(m,s1);
GETSTRING getstringns2(n,s2);
if ((m==-1)||(n==-1))
return (s1+s2);
else
{
m += n;
ostringstream oss;
oss << m;
return oss.str();
}
}


inline int MyFind()	// find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回 ?? 哪个 ？？ 字符串的长度。
{
string s;
int n,value;
cin >> s;
GETINT getintn(n);
value = str[n].find(s);
if (value==string::npos)
value = str[n].length();
return value;
}

inline int MyRfind()	// rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
{
string s;
int n,value;
cin >> s;
GETINT getintn(n);
value = str[n].rfind(s);
if (value==string::npos)
value = str[n].length();
return value;
}

inline void MyInsert()	// insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
{
string s;
int n,x;
GETS Gets(s);
GETINT getintn(n);
GETINT getintx(x);
str[n].insert(x,s);
}

inline void MyReset()	// reset S N：将第N个字符串变为S。
{
string s;
int n;
GETS Gets(s);
GETINT getintn(n);
str[n].assign(s);
}
