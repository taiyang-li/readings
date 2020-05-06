#ifndef _SINGLETON0_
#define _SINGLETON0_

#include <boost/noncopyable.hpp>

template <typename T>
class Singleton0 : public boost::noncopyable
{
    public:
        static T& instance()
        {
            if (_value == NULL)
            {
                _value = new T();
            }
            return *_value;
        }

    private:
        Singleton0();
        ~Singleton0();

    private:
        static T* _value;
};


template <typename T>
T* Singleton0<T>::_value = NULL;

#endif
