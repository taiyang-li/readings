#include <cstdio>
#include <new>
#include <iostream>

using namespace std;

struct  Big
{
	double stuff[20000];
};

int main()
{
	Big *pb;
	try 
	{
		cout << "trying to get a big block of memory" << endl;
		pb = new Big[10000];  
		cout << "got passed the new request" << endl;
	}
	catch(bad_alloc &ba)
	{
		cout << "caught the exception" << endl;
		cout << ba.what() << endl;
		exit(EXIT_FAILURE);
	}
	cout << "memory located successfully" << endl;
	pb[0].stuff[0] = 4;
	cout << pb[0].stuff[0] << endl;
	delete [] pb;
	return 0;
}
