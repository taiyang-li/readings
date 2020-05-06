#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
typedef struct
{
	long int nType;
	char szText[256];
}MSG;
main()
{
	key_t lKey;
	int nMsgId;
	MSG msg;
	if((lKey = ftok("/etc/profile",1)) == -1)//生成键值
	{
		perror("ftok");
		exit(1);
	}
	if((nMsgId = msgget(lKey,IPC_CREAT|IPC_EXCL|0666)) == -1)//创建消息队列
	{
		if(errno != EEXIST)
		{
			perror("msgget");
			exit(2);
		}
		if((nMsgId = msgget(lKey,0)) == -1)
		{
			perror("msgget");
			exit(3);
		}
	}
	memset(&msg,0x00,sizeof(MSG));//清空队列
	msg.nType = 2;//指定消息类型为2
	memcpy(msg.szText,"123456",6);//指定消息内容
	if(msgsnd(nMsgId,(const void *)&msg,strlen(msg.szText),IPC_NOWAIT) < 0)//非阻塞发送消息
	{
		perror("msgsnd");
	}
	return 0;
}
