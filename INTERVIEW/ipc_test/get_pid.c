#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	// pid ppid grpid
	printf("process id = %d\n", getpid());
	printf("parent process id = %d\n", getppid());
	printf("process group id = %d\n", getpgrp());
	
	// user grp 
	printf("calling process's real user id = %d\n", getuid());
	printf("calling process's real grp  id = %d\n", getgid());
	printf("calling process's effective user id = %d\n", geteuid());
	printf("calling process's effective grp  id = %d\n", getegid());
	return 0;
	
	
}
