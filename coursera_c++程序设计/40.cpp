#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
class A
{
    private:
        int _n;
    public:
        static int count;
        A() : _n(0) { 
            count++;
        }
        A(int n) : _n(n) {
            count++;
        }
        virtual ~A()
        {
            cout << "A::destructor" << endl;
        }
        
        void operator delete(void* a)
        {
            count--;
        }
};

class B : public A
{
    public:
        B() : A() {}
        B(int n) : A(n) {}

/*
        B &operator=(B &b) {
            return b;
        }
*/
        virtual ~B()
        {
            cout << "B::destructor" << endl;
        }
};
int A::count = 0;
void func(B b) {
}
int main()
{
    A a1(5),a2;
    cout << A::count << endl;
    B b1(4);
    cout << A::count << endl;
    func(b1);
    cout << A::count << endl;
    A * pa = new B(4);
    cout << A::count << endl;
    delete pa;
    cout << A::count << endl;
    return 0;
}
