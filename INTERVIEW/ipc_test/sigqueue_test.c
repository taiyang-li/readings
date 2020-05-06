#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void handle_signal(int signo, siginfo_t *info, void *none)
{
	printf("receive addtional data is %d\n", info->si_value.sival_int);
	exit(0);
}

int main()
{
	int pid;
	struct sigaction act;
	union sigval sigvalPara;

	if ((pid = fork()) == 0)
	{
		memset(&act, 0x00, sizeof(struct sigaction));
		sigemptyset(&act.sa_mask);
		act.sa_sigaction = handle_signal;
		act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGINT, &act, NULL) == -1)
		{
			perror("sigaction");
			exit(0);
		}
		pause();
	}
	else if (pid > 0)
	{
		sigvalPara.sival_int = 123;
		if (sigqueue(pid, SIGINT, sigvalPara) == -1)
		{
			perror("sigqueue");
			exit(0); 
		}
	}
}
