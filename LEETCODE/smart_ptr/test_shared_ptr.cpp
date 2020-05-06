#include <memory>
#include <iostream>
#include "shared_ptr.h"
 
struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 
struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete from function object...\n";
        delete p;
    }
};
 
int main()
{
    {
        std::cout << "constructor with no managed object\n";
        SharedPtr<Foo> sh1;
    }
 
    {
        std::cout << "constructor with object\n";
        SharedPtr<Foo> sh2(new Foo);
        SharedPtr<Foo> sh3(sh2);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }
    return 0;
}

