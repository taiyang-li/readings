#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main()
{	
	short int a = 0x1122;
	char b = *(char*)&a;
	if (b == 0x11)
		cout << "big endian\n" << endl;
	else
		cout << "little endian\n" << endl;
	getchar();
	return 0;
	
}

