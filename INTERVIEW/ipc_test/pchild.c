#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	fprintf(stderr, "fork...\n");
	if (fork() == 0)  // child process
	{
		wait();
		exit(0);
	}
	printf("AA");
	sleep(10);
	exit(0);
}
