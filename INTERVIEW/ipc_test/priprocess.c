#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
	int nPr;
	
	if (nice(3) == -1)
	{
		perror("nice");
		exit(0);
	}
	
	errno = 0;
	nPr = getpriority(PRIO_PROCESS, getpid());
	if (errno != 0)
	{
		perror("get proority");
		exit(0);
	}

	printf("priority is %d\n",nPr);
	return 0;
}
