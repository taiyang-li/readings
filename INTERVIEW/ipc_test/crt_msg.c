#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>




struct msgbuf
{
	long int mtype;
	char mtext[1];
};


int main()
{	
	key_t IKey;
	int nMsgld;
	if (IKey = ftok("/etc/profile", 1) == -1)
	{
		perror("ftok error!\n");
		exit(1);
	}

	// create msg queue
	if (nMsgld = msgget(IKey, IPC_CREAT|IPC_EXCL|0666) == -1)
	{
		if(errno != EEXIST)
		{
			perror("msgget error!\n");
			exit(2);
		}
			
		//if (nMsgld = msgget(IKey, 0) == -1) 
		//{
		//	perror("msgget error!\n");
		//	exit(3);
		//}
	}
	
	printf("msg id = %d\n", nMsgld);
	return 0;

	
	
}


