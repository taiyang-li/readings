/* echo-timeout.c
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** echo-timeout.c                                                        ***/
/***                                                                       ***/
/*** Demonstrate how to constrol the timeout on a connection.              ***/
/*****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>

void PANIC(char *msg);
#define PANIC(msg) {perror(msg);abort();}
#define TIMEOUT		5

struct sigaction act;

/*--------------------------------------------------------------------*/
/*--- Signal capture: SIGCHLD & SIGALRM                            ---*/
/*--------------------------------------------------------------------*/
void sig_handler(int sig)
{   int retval;

	switch ( sig )
	{
		case SIGCHLD: wait(&retval); break;
		case SIGALRM: break; /* do nothing--acknowledge signal */
	}
}

/*--------------------------------------------------------------------*/
/*--- child - process connection; if timeout, exit                 ---*/
/*--------------------------------------------------------------------*/
void child(int sd)
{	int bytes;
	char line[100];
	char *msg_timeout = "Timeout--too much delay!\n";
	char *msg_reply = "ECHO: ";
	char *msg_end = "bye\r";

	act.sa_flags = SA_ONESHOT;
	if ( sigaction(SIGALRM, &act, 0) < 0 )
		PANIC("SigAction--can't install timeout");
	do
	{
		alarm(TIMEOUT);
		bytes = recv(sd, line, sizeof(line), 0);
		if ( bytes < 0 )
			if ( errno == EINTR )
			{
				fprintf(stderr, "Connection timed out\n");
				send(sd, msg_timeout, strlen(msg_timeout), 0);
				close(sd);
				exit(0);
			}
			else
				perror("Recv");
		send(sd, msg_reply, strlen(msg_reply), 0);
		send(sd, line, bytes, 0);
	}
	while ( bytes > 0  &&  strncmp(msg_end, line, strlen(msg_end)) != 0 );
	close(sd);
	exit(0);
}

/*--------------------------------------------------------------------*/
/*--- main - set up server and signal handler and await connections---*/
/*--------------------------------------------------------------------*/
int main(int count, char *strings[])
{	int sd;
	struct sockaddr_in addr;

	if ( count < 2 )
	{
		printf("Usage: timeout-server <portnum>\n");
		exit(0);
	}
	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART;
	if ( sigaction(SIGCHLD, &act, 0) < 0 )
		PANIC("SigAction--can't install sigchild");
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if ( sd < 0 )
		PANIC("Socket");
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(strings[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
		PANIC("Bind");
	if ( listen(sd, 20) < 0 )
		PANIC("Listen");
	for (;;)
	{	int client, size=sizeof(addr);

		client = accept(sd, (struct sockaddr*)&addr, &size);
		if ( client > 0 )
		{
			printf("%s:%d connected\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
			if ( !fork() )
				child(client);
			else
				close(client);
		}
		else
			perror("Accept");
	}
	return 0;
}

