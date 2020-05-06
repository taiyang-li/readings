#include <unistd.h>
#include <stdio.h>


int main()
{
	setpgid(0,0);
	sleep(8); 
}
