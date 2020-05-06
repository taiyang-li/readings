#ifndef __EFFECTIVE_CPP_LOCK_H__
#define __EFFECTIVE_CPP_LOCK_H__

#include <pthread.h>

class Lock
{
  public:
    Lock(pthread_mutex_t& key) 
      : key_(key) 
    {
      ::pthread_mutex_lock(&key_);
    }

    ~Lock()
    {
      ::pthread_mutex_unlock(&key_);
    }

  private:
    ::pthread_mutex_t& key_;
};

class BaseLock
{
  public:
    BaseLock(::pthread_mutex_t& key) {}
    virtual ~BaseLock() {}
};

class MutexLock : public BaseLock 
{
  public:
    MutexLock(::pthread_mutex_t& key) 
      : BaseLock(key), key_(key)
    {
      ::pthread_mutex_lock(&key_);
#if defined(DEBUG)
      std::cout << "lock:" << &key_ << std::endl;
#endif
    }

    ~MutexLock()
    {
      ::pthread_mutex_unlock(&key_);
#if defined(DEBUG)
      std::cout << "unlock:" << &key_ << std::endl;
#endif
    }

  private:
    ::pthread_mutex_t& key_;
};

#endif  /*LOCK_H*/
