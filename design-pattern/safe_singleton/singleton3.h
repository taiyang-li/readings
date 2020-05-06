#ifndef _SINGLETON3_
#define _SINGLETON3_

#include <boost/noncopyable.hpp>
#include <pthread.h>

template <typename T>
class Singleton3 : public boost::noncopyable
{
    public:
        static T& instance()
        {
            ::pthread_mutex_lock(&_mutex);
            static T t;
            ::pthread_mutex_unlock(&_mutex);
            return t;
        }

    private:
        Singleton3()
        {
            ::pthread_mutex_init(&_mutex, NULL);
        }

        ~Singleton3()
        {
            ::pthread_mutex_destroy(&_mutex);
        }

    private:
        static ::pthread_mutex_t _mutex;
};

template <typename T>
::pthread_mutex_t Singleton3<T>::_mutex;

#endif
