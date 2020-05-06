#include <stdio.h>
#include <signal.h>

void handle_signal(int signo, siginfo_t *info, void *none)
{	
	printf("receive signal %d, addtional data is %d\n",signo, info->si_value.sival_int);

}


int main()
{
	struct sigaction act, oact;
	
	memset(&act, 0x00, sizeof(struct sigaction));
	
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handle_signal;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &act, &oact) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	
	pause();
	exit(0);
	
}
