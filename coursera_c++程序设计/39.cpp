#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A 
{
    protected:
        char _type;
        int _age;

    public:
        A(int n) : _age(n) {
            _type = 'A';
        } 

        int get_age() const
        {
            return _age;
        }
        char get_type() const
        {
            return _type;
        }
};

class B : public A
{   
    public:
        B(int n) : A(n)
        {
            _type = 'B';
        }
};

class Comp
{
    public:
        bool operator()(A const *m, A const *n)
        {
            return m->get_age() < n->get_age();
        }
};

/*
class Print
{
    private:
        A* _ptr;
    public:
        Print(A* ptr) : _ptr(ptr) {}

        void operator()
        {
            cout << _ptr->get_type() << " " << _ptr->get_age() << endl;
        }
};
*/

void Print(const A* p)
{
    cout << p->get_type() << " " << p->get_age() << endl;
}


int main()
{

    int t;
    cin >> t;
    set<A*,Comp> ct;
    while( t -- ) {
        int n;
        cin >> n;
        ct.clear();
        for( int i = 0;i < n; ++i)   {
            char c; int k;
            cin >> c >> k;

            if( c == 'A')
                ct.insert(new A(k));
            else
                ct.insert(new B(k));
        }
        for_each(ct.begin(),ct.end(),Print);
        cout << "****" << endl;
    }
}
