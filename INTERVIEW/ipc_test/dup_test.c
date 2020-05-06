#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{	
	int pfds[2];
	if (pipe(pfds) == 0)
	{
		close(1);  // close stdout
		dup2(pfds[1], 1);
		close(pfds[0]);
		execlp("ls", "ls", "-l", NULL);
	}
	else
	{
		close (0);
		dup2(pfds[0], 0);
		close(pfds[1]);
		execlp("wc", "wc", "-l", NULL);  
	}
}
