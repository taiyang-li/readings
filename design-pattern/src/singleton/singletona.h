#ifndef _SINGLETON_A_H_
#define _SINGLETON_A_H_

#include "singleton.h"

class SingletonB : public Singleton
{
	friend class Singleton;

	protected:
		SingletonB() {}

	public:
		void show()
		{
			cout << "this is Singleton B showing" << endl;
		}
};

#endif


