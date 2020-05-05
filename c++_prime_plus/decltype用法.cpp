#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{	
	
	system("pause");
	return 0;
}



// 1
template <class U, class V>
void Somefunction(U u, V v)
{
	// result = u*v;
	decltype(u*v) result = u*v;
}

// 2
int add(int i, int j) {return i+j;}
decltype(add(5,6)) var = 5;


// 3
struct M {double x;};
double pi = 3.14;
const M* m = new M();
decltype((m->x)) piRef = pi;



// 4 delctype不会执行表达式 auto会， 仅仅推论表达式类型
int foo() {}
decltype(foo()) x;


// 5 跟踪返回功能
template<class U, class V>
auto multiply(U u, V v) ->decltype(u*v)
{
	return u*v;
}
