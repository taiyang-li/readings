#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t IKey;
	int nShmld;
	
	if ((IKey = ftok("/etc/profile", 1)) < 0)
	{
		perror("ftok\n");
		exit(1);
	}

	if (nShmld = shmget(IKey, 256, IPC_CREAT | 0666) == -1)
	{
		perror("shmget\n");
		exit(2);
	}

	printf("Shmid=%d\n", nShmld);
	return 0;
}
