#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>


typedef struct 
{
	int n;
	char str[256];
} SHM;


int main()
{
	key_t IKey;
	int nShmld;
	SHM *p;
	
	// get the key
	if ((IKey = ftok("/etc/profile", 2)) < 0)
	{
		perror("ftok");
		exit(1);
	}
	
	// get the id for shm
	if ((nShmld = shmget(IKey, sizeof(SHM), IPC_CREAT|0666)) < 0)
	{
		perror("shmget");
		exit(2);
	}
	

	// get the pointer from the id
	if ((p = shmat(nShmld, NULL, 0)) == (void *) -1)
	{
		perror("shaat");
		exit(3);
	}


	// change memory content
	p->n = 1;
	strcpy(p->str, "123456");
	if (shmdt(p) == -1)
	{
		perror("shmdt");
		exit(4);
	}
	return 0;	
}
