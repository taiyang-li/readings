#include <stdio.h>
#include <signal.h>

void handle_signal(int signo)
{	
	printf("receove signal %d\n", signo);
}


int main()
{
	sigset_t mask;
	sigset_t omask;
	sigset_t pmask;
	signal(SIGINT, handle_signal);

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigprocmask(SIG_BLOCK, &mask, &omask);
	sleep(10);
	
	if (sigpending(&pmask) < 0)
	{
		perror("sigpending");
		exit(1);
	}

	if (sigismember(&pmask, SIGINT))
		printf("SIGINT signal is pending\n");



}
