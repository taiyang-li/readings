#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



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
	
	if ((IKey = ftok("/etc/profile", 1)) == -1)
	{
		perror("ftok\n");
		exit(2);
	}

	if ((nMsgld = msgget(IKey, 0)) == -1)
	{
		perror("msgget\n");
		exit(3);
	}

	// msg rcv
	memset(&msg, 0, sizeof(MSG));
	if ((n=msgrcv(nMsgld, (void *)&msg, sizeof(msg.szText), 2L, 0)) < 0)
		perror("msgrcv\n");
	else
		printf("msgrcv return length=[%d] text=[%s]\n", n, msg.szText);
	return 0;
}

