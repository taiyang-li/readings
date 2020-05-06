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





// 第53-54题
//class A
//{
//public:
//	A() {printf("A");}
//	~A() {printf("~A");}
//};
//
//class B
//{
//public:
//	B(A &a) : _a(a)
//	{
//		printf("B");
//	}
//	~B()
//	{
//		printf("~B");
//	}
//
//private:
//	A _a;
//};
//
//int main ()
//{
//	A a;
//	B b(a);
//	// delete b;
//	// delete a;
//
//	system("pause");
//	return 0;
//}


//// 第59题
//struct IU
//{
//	virtual void QI(void **p) = 0;  // 纯虚函数
//};
//
//struct IA : public IU
//{
//	virtual void func() = 0;
//};
//
//struct IB : public IU
//{
//	virtual void func() = 0;  
//};
//
//class C : public IA, public IB 
//{
//public:
//	void IA::func()
//	{
//		printf("IA func\n");
//	}
//	void IB::func()
//	{
//		printf("IB func\n");
//	}
//	void QI(void **p)
//	{
//		*p = (IA*)this;
//	}
//};
//
//
//int main()
//{
//	C c;
//	IB *pB = &c;
//	IA *pA;
//	pB->QI((void **)&pA);
//	pA->func();
//	pB->func();
//
//	getchar();
//	return 0;
//}

//// 第60题
//class A
//{
//public:
//	virtual void Test() 
//	{
//		printf("A test\n");
//	}
//};
//
//class B : public A
//{
//public:
//	void func() {Test();}
//	virtual void Test() {printf("B Test\n");}
//};
//
//class C : public B
//{
//public:
//	virtual void Test() {printf("C Test");}
//};
//
//int main()
//{
//	C c;
//	((B *)(&c))->func();  
//	((B)c).func();
//	
//	getchar();
//	return 0;
//}



//// 第68题
//class A
//{
//public:
//	A()
//	{
//		printf("1");
//	}
//	A(A &a)
//	{
//		printf("2");
//	}
//	A& operator=(const A& a)
//	{
//		printf("3");
//		return *this;
//	}
//};
//
//int main()
//{
//	A a;
//	A b=a;
//	getchar();
//	return 0;
//}


// 第76题
//struct A_
//{
//	A_ a;
//};

//struct A
//{
//	A* _a;
//};


//struct A
//{
//	A& _a;
//};
//
//
//int main()
//{
//	struct A a;
//	getchar();
//	return 0;
//}


// 第91题
//class A
//{
//public: 
//	A() {} 
//	void foo() {printf("%d\n", A::i);}
//private:
//	static int i;
//};
//
//int main()
//{
//	A a;
//	a.foo();
//
//	getchar();
//	return 0;
//}


//// 第90题
//typedef void (*PFN)();
//class A
//{
//
//	
//private:
//	void run(PFN pfn) {pfn();}
//	void func() {printf("run\n");}
//public:
//	void foo() {run((PFN)func);}
//};
//
//void main()
//{
//	A a;
//	a.foo();
//
//	getchar();
//	return 0;
//}
