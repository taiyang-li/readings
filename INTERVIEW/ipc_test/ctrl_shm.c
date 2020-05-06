#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
	struct shmid_ds sds;
	
	if ((IKey = ftok("/etc/profile", 3)) == -1)
	{
		perror("ftok");
		exit(1);
	}


	if ((nShmld = shmget(IKey, 256, IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(2);
	}
	
	// stat of shm
	memset(&sds, 0, sizeof(struct shmid_ds));
	if (shmctl(nShmld, IPC_STAT, &sds) < 0)
	{
		perror("shmctl IPC_STAT");
		exit(3);
	}

	//  set the stat of shm
	printf("first shm_perm.mode=0%o\n", sds.shm_perm.mode);
	sds.shm_perm.mode &= (~0002);
	if (shmctl(nShmld, IPC_SET, &sds) < 0)
	{
		perror("shmctl IPC_SET");
		exit(3);
	}
	
	// stat of shm
	memset(&sds, 0x00, sizeof(struct shmid_ds));
	if (shmctl(nShmld, IPC_STAT, &sds) < 0)
	{
		perror("shmctl IPC_STAT");
		exit(5);
	}

	// clear shm
	printf("second shm_perm.mode=0%o\n", sds.shm_perm.mode);
	if (shmctl(nShmld, IPC_RMID, NULL) < 0)
	{
		perror("shmctl IPC_RMID");
		exit(6);
	}

	return 0;
}
