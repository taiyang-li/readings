#ifndef _SINGLETON_B_H_
#define _SINGLETON_B_H_

#include "singleton.h"
class SingletonA : public Singleton
{
	friend class Singleton;

	protected:
		SingletonA() {}

	public:
		void show() 
		{
			cout << "this is Singleton A showing" << endl;
		}
};

#endif


