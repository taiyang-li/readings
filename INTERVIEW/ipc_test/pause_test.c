#include <stdio.h>
#include <signal.h>


int nInterrupt;

void handle_sigint(int signo)
{
	nInterrupt = 1;
}


int main()
{
	sigset_t mask, omask;
	signal(SIGINT, handle_sigint);
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigprocmask(SIG_BLOCK, &mask, &omask);
	nInterrupt = 0;
	
	while(!nInterrupt)
	{
		sigsuspend(&omask);
	}
	printf("process return \n");

}
