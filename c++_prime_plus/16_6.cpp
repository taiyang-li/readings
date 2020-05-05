#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>




using namespace std;





int main()
{
	unique_ptr<string> films[5] = 
	{
		unique_ptr<string> (new string("liyang")),
		unique_ptr<string> (new string("limeiling")),
		unique_ptr<string> (new string("litaiting")),
		unique_ptr<string> (new string("liping")),
		unique_ptr<string> (new string("lixing"))
	};
	
	unique_ptr<string> pwin;
	pwin = films[2];
	
	for (int i=0; i<5; i++)
		cout << *films[i] << endl;
	
	cout << "the winner is " << *pwin << endl;
	
	system("pause");
	return 0;
}
