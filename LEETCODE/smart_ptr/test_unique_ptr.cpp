#include <memory>
#include <iostream>
#include "unique_ptr.h"
 
struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 

int main()
{
    {
        std::cout << "constructor with no managed object\n";
        UniquePtr<Foo> sh1;
    }
 
    {
        std::cout << "constructor with object\n";
        UniquePtr<Foo> sh2(new Foo);
        UniquePtr<Foo> sh3(sh2);
    }
    return 0;
}

