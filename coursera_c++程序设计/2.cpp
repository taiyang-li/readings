#include <iostream>
using namespace std;
class A {
public:
    int val;

	A() {
		val = 0;
	}
	
	A(int n)
	{
		val = n;
	}

	int GetObj() const 
	{
		return val;
	}

	int& GetObj() 
	{
		return val;
	}
};

main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
}
