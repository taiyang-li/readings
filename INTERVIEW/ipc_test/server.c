/***************************************************************************************************************************************************************************
 *  *文件:service.c
 *   *描述：服务器端程序,接收客户端请求消息，发送确认回执“--OK”
 *    */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 4321
#define MAX_NUM 5 //指定允许等待的最大连接数
#define BUFFERSIZE 1024


int main()
{
	int sockfd;
	struct sockaddr_in server_addr;//socket地址结构
	// 创建socket端口,函数原型：int socket(int domain,int type,int protocol);
	//指定了IPV4协议，字节流传输
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd == -1)
	{
		perror("Creat socket fail:");
		exit(1);
	}
	else
	{
		printf("Server creat socket success!\n");
	}


	//创建socket后进行地址绑定，调用bind函数，原型：
	//int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
	server_addr.sin_family = AF_INET;//使用IPV4协议
	server_addr.sin_addr.s_addr = INADDR_ANY;//sockaddr_in机构体中成员sin_addr结构体中s_addr成员表示一个32位的IPV4地址
	server_addr.sin_port = htons(PORT);//htons函数将主机字节序转换为网络
	bzero(&(server_addr.sin_zero),8);//将结构体中用于对齐的数组填充0

	if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("Bind error:");
		exit(1);
	}
	else
	{
		printf("Server bind success!\n");
	}
	//调用listen函数进行监听
	//函数原型：int listen(sockfd,int backlog);
	if(listen(sockfd,MAX_NUM) < 0)
	{
		perror("Listen error:");
		exit(1);
	}
	else 
	{
		printf("Server listen success:\n");
	}

	while(1)
	{
		int client_fd;//用于表示链接上的sockfd
		struct sockaddr_in client_addr;
		socklen_t length = sizeof(client_addr);

		//调用accept函数等待客户端链接
		if((client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&length)) < 0)
		{
			perror("Server accept error:");
			exit(1);
		}
		else
		{
			printf("Server acept success:\n");
			printf("Create connection with %s\n", inet_ntoa(client_addr.sin_addr));
		}


		char recvbuf[BUFFERSIZE] = {0};
		char sendbuf[BUFFERSIZE] = {0};
		//调用recv和send函数进行接收和发送操作
		if(recv(client_fd,recvbuf,BUFFERSIZE,0) == -1)
		{
			perror("!!!!\n");
			printf("Recv error!\n");
			break;
		}
		else
		{
			//打印接收到的信息，并且返回确认消息
			printf("Recvived message :%s\n",recvbuf);
			strcpy(sendbuf,recvbuf);
			strcat(sendbuf,"--OK");
			if(send(client_fd,sendbuf,strlen(sendbuf),0) == -1)
			{
				printf("Server send error!\n");
				break;
			} 

		}
		//关闭socket
		close(client_fd);
	}


	exit(0);
}

