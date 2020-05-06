#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigcld(int signo)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, 0);
	printf("child process %d exit with code %d\n", pid, status);
}



int main()
{
	int i;
	int pid;
	signal(SIGCLD, handle_sigcld);
	for (i=0; i<5; i++)
	{
		if ((pid = fork()) == 0)  // child
		{
			srand(getpid());
			exit((int)(rand()/1024));
		}
		else
		{
			sleep(1);
			continue; 
		}
	}
}
