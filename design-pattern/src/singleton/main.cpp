#include "singleton.h"

int main()
{
	Singleton* st = Singleton::getInstance("SingletonA");
	st->show();
	return 0;
}
