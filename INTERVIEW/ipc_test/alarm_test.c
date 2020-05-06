#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int timeout;

void handle_alarm(int signo)
{
	timeout = 1;
	printf("SIGALRM received\n");
}

int main()
{
	if (signal(SIGALRM, handle_alarm)  == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}


	timeout = 0;
	alarm(10);  // start the timer 
	pause();    // block process and wait for signal
	if (timeout) // time out
	{
		printf("pause time out");
	}
	exit(0);
}
