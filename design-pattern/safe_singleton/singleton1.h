#ifndef _SINGLETON1_
#define _SINGLETON1_

#include <boost/noncopyable.hpp>
#include <pthread.h>


template <typename T>
class Singleton1 : public boost::noncopyable
{
    public:
        static T& instance()
        {
            ::pthread_once(&_ponce, &Singleton1::init);
            return *_value;
        }

    private:
        Singleton1();
        ~Singleton1();

        static void init()
        {
            _value = new T();
        }

    private:
        static T* _value;
        static ::pthread_once_t _ponce;
};


template <typename T>
T* Singleton1<T>::_value = NULL;

template <typename T>
::pthread_once_t Singleton1<T>::_ponce = PTHREAD_ONCE_INIT;

#endif
