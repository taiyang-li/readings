#ifndef _SINGLETON2_
#define _SINGLETON2_

#include <boost/noncopyable.hpp>
#include <pthread.h>


template <typename T>
class Singleton2 : public boost::noncopyable
{
    public:
        static T& instance()
        {
            if (_value == NULL)
            {
                ::pthread_mutex_lock(&_mutex);
                if (_value == NULL)
                {
                    _value = new T();
                }
                ::pthread_mutex_unlock(&_mutex);
            }
            return *_value;
        }

    private:
        Singleton2()
        {
            ::pthread_mutex_init(&_mutex, NULL);
        }

        ~Singleton2()
        {
            ::pthread_mutex_destroy(&_mutex);
        }

    private:
        static T* _value;
        static ::pthread_mutex_t _mutex;
};


template <typename T>
T* Singleton2<T>::_value = NULL;

template <typename T>
::pthread_mutex_t Singleton2<T>::_mutex;

#endif
