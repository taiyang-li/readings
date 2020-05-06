#ifndef _SINGLETON4_
#define _SINGLETON4_

#include <boost/noncopyable.hpp>
#include <pthread.h>

template <typename T>
class Singleton4 : public boost::noncopyable
{
    public:
        static T& instance()
        {
            return *_value;
        }

    private:
        Singleton4();
        ~Singleton4();

    private:
        static T* _value;
};

template <typename T>
T* Singleton4<T>::_value = new T();

#endif
