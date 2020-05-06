#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


int main()
{
	pid_t pid;
	
	//signal(SIGCLD, SIG_IGN);// ignore SIGCLD
	
	switch(pid=fork())
	{
		case -1:
			perror("fork");
			break;
		case 0: // child
			printf("child : id = %d\n", getpid());
			printf("pid = %d\n", pid);
			exit(0);
			break;
		default: // father
			printf("father: id = %d\n", getpid());
			printf("pid = %d\n", pid); 
			sleep(5);
			break;
			
			
	}
}
