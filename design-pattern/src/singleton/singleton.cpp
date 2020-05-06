#include "singleton.h"
#include "singletona.h"
#include "singletonb.h"

class SingletonA;
class SingletonB;

Singleton* Singleton::_instance = NULL;
Singleton* getInstance(const char* name)
{
	if (_instance == NULL)
	{
		if(strcmp(name, "SingletonA") == 0)
		{
			_instance = new SingletonA();
		}
		else if (strcmp(name, "SingletonB") == 0)
		{
			_instance = new SingletonB();
		}
		else
		{
			_instance = new Singleton();
		}
	}
	return _instance; 
}


