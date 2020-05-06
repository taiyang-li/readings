#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <iostream>
#include <cstring>
using namespace std;

class Singleton
{
	public:
		static Singleton* getInstance(const char* name);

		virtual void show() {}

	protected:
		Singleton() {}

	private:
		static Singleton* _instance;
};

#endif
