#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct 
{
	long int nType;
	char szText[256];
} MSG;


int main()
{
	key_t IKey;
	int n;
	int nMsgld;
	MSG msg;
	struct msqid_ds qds;
	
	if ((IKey = ftok("/etc/profile", 1)) == -1)
	{
		perror("ftok\n");
		exit(2);
	}
	
	if ((nMsgld = msgget(IKey, 0))  == -1)
	{
		perror("msgget\n");
		exit(3);
	}
	
	memset(&qds, 0, sizeof(struct msqid_ds)); 
	if (msgctl(nMsgld, IPC_STAT, &qds) < 0)
	{
		perror("msgctl IPC_STAT\n");
		exit(4);
	}


	// show info 
	memset(&msg, 0, sizeof(MSG));
	msg.nType = 2;
	memcpy(msg.szText, "12345", 5);


	// send msg
	if (msgsnd(nMsgld, (const void *)&msg, strlen(msg.szText), 0) < 0)
		perror("msgsnd\n");
	
	
	// del msg
	if (msgctl(nMsgld, IPC_RMID, NULL) < 0)
	{
		perror("msgctl IPC_RMID");
		exit(5);
	}

	return 0;
}
