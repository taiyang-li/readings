#include <iostream>
#include <memory>

class B;
class A {
public:
    A() {
        std::cout << "contruct A" << std::endl;
    }
    
    ~A() {
        std::cout << "destruct A" << std::endl;
    }

    std::weak_ptr<B> _b;
};

class B {
public:
    B() {
        std::cout << "construct B" << std::endl;
    }

    ~B() {
        std::cout << "destruct B" << std::endl;
    }

    std::weak_ptr<A> _a;
};

std::shared_ptr<A> a;
std::shared_ptr<B> b;

void observe(std::shared_ptr<A> a) {
    std::cout << "a user_count:" << a.use_count() << std::endl;
    if (auto wb = a->_b.lock()) {
        std::cout << "b weak_ptr valid" << std::endl;
    } else {
        std::cout << "b weak_ptr invalid" << std::endl;
    }
}

int main() {
    a.reset(new A());
    b.reset(new B());
    a->_b = b;
    b->_a = a;
    observe(a);
    return 0;
}
