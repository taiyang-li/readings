#include <iostream>

using namespace std;

class myclass

{

	static const char name[20];//¸ÄÎªstatic

	public:

	myclass(){}

	void show()

	{

		for ( int i=0;i<20;++i )

		{

			cout<<name[i];

		}

	}

};

const char myclass::name[20] = {'a','b','c','d','\0'};

main ()

{

	myclass a;

	a.show();

}
