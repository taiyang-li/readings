#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
	pid_t pid;
	char *para[] = {"ls", "-a", NULL};
	

	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	
	if (pid == 0)  // child
	{
		if (execl("/bin/ls", "ls", "-l", (char *)0) == -1)
		{
			perror("execl");
			exit(0);
		}
	}
	

	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(0);
	}

	if (pid == 0)
	{
		if (execv("/bin/ls", para)  == -1)
		{
			perror("execv");
			exit(0);
		}
	}

	return;

	
}
