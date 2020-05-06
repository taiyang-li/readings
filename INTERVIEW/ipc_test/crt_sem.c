#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>

int main()
{
	int semid;
	key_t semkey;
	
	// ftok
	if ((semkey = ftok("/etc/profile",1)) < 0)
	{
		perror("ftok");
		exit(1);
	}

	// semget 
	if ((semid = semget(semkey, 1, IPC_CREAT | 0666)) < 0)
	{
		perror("semget");
		exit(2);
	}
	
	// print
	printf("semid = %d\n", semid);

	return 0;
}

