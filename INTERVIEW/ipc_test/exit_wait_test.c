#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>



void handle_sigcld(int signo)
{
	pid_t pid;
	int status;
	
	if ((pid = wait(&status)) == -1)
	{
		printf("child %d exit\n", pid);
	}

	if (WIFEXITED(status))
	{
		printf("child return %d\n", WEXITSTATUS(status));
	}
	
	if (WIFSIGNALED(status))
	{
		printf("child terminated by %d\n", WTERMSIG(status));
	}
}

int main()
{
	pid_t pid;

	signal(SIGCLD, handle_sigcld);

	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}


	if (pid == 0)
	{
		exit(123);
	}
	sleep(10);
}
