#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <unistd.h>

int main()
{
	int n;
	__pid_t nPid;
	__pid_t nGroupld;
	
	if ((nPid = fork()) < 0)
	{
		printf("error");
		exit(0);
	}


	if (nPid != 0)  // father process
	{
		perror("aaa");
		wait(0);
	}
	else  // child process
	{
		perror("bbb");
		nGroupld = setsid();  // crt new session 
		if (nGroupld == -1)
		{
			perror("setsid");
			exit(0);
		}
		perror("fff");
		sleep(3);
		perror("ggg");
		exit(0);
	}
	perror("kkk");
}
