#include "singleton0.h"
#include "singleton1.h"
#include "singleton2.h"
#include "singleton3.h"
#include "singleton4.h"

int main()
{
    ::Singleton0<int>::instance();
    ::Singleton1<int>::instance();
    ::Singleton2<int>::instance();
    ::Singleton3<int>::instance();
    ::Singleton4<int>::instance();
    return 0;
}
