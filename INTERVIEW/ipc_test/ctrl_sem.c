#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>



typedef union semum
{
	int val;
	struct semid_ds *buf;
	unsigned short *array; 
} SEMCTL_UNION;

int main()
{
	int n;
	int semid;
	key_t semkey;
	SEMCTL_UNION semctl_arg;
	struct sembuf buf;
	
	if ((semkey = ftok("/etc/profile", 1)) < 0)
	{
		perror("ftok");
		exit(1);
	}
	
	if ((semid = semget(semkey, 1, 0)) < 0)
	{
		perror("semget");
		exit(2);
	}
	
	// set sem 
	semctl_arg.val = 2;
	if (semctl(semid, 0, SETVAL, semctl_arg) < 0)
	{
		perror("semctl SETVAL");
		exit(3);
	}

	/// set sem 
	memset(&buf, 0x00, sizeof(struct sembuf));
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = IPC_NOWAIT;
	for (n=0; ; n++)
	{
		if (semop(semid, &buf, 1) == -1)
		{
			perror("semop");
			exit(5);
		}
		printf("semop[%d]: current semphore value = %d\n", n, semctl(semid, 0, GETVAL, semctl_arg));
	}
	
	
	return 0;
}
