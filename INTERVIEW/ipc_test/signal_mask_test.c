#include <stdio.h>
#include <signal.h>

void handle_sigint(int signo)
{
	printf("receive signal %d\n", signo);
}


int main()
{
	sigset_t mask;
	sigset_t omask;
	signal(SIGINT, handle_sigint);
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigprocmask(SIG_BLOCK, &mask, &omask);
	sleep(10);
	sigprocmask(SIG_SETMASK, &omask, NULL);
	exit(0);
}
