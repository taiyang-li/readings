/******************************************************************************************************************************************************************************
 *  *文件：client.c
 *   *描述:向服务器端发送一个消息，并且得到确认
 *    * 向服务器发送消息，并且收到服务器的确认消息"--OK"，打印在终端上
 *     */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>




#define PORT 4321
#define BUFFERSIZE 1024


int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("Usage:./%s ServerAddress \n",argv[0]);
		exit(1);
	}


	struct sockaddr_in server_addr;
	int connected;
	char sendbuf[BUFFERSIZE] = {0};
	char recvbuf[BUFFERSIZE] = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_aton(argv[1],&server_addr.sin_addr);//该函数将参数argv[1]转换为32位地址
	bzero(&(server_addr.sin_zero),8);
	//创建sockfd
	if((connected = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("Client creat socket error:");
		exit(1);
	}


	//调用connect函数，主动连接服务器
	if(connect(connected,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("Connect error:");
		exit(1);


	}
	else
	{
		printf("Connect success:\n");
		printf("Input message: \n");
		scanf("%s",sendbuf);
	} 


	//发送和接收消息
	if(send(connected,sendbuf,strlen(sendbuf),0) < 0)
	{
		perror("Send error:");
		exit(1);
	}
	else
	{
		if(recv(connected,recvbuf,BUFFERSIZE,0) < 0)
		{
			perror("Recv error:");
			exit(1);
		}
	}

	printf("The message from server:%s\n",recvbuf);
	close(connected);
	exit(0);
}




