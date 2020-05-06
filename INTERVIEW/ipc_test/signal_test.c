#include <stdio.h>
#include <signal.h>

void  handle_signal(int signo)
{
	printf("receive signal %d\n", signo);
}


int main()
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}


	pause(); // wait until signal comes	
	exit(0);
}
