/* heartbeat-client.c
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
/*** heartbeat-client.c                                                    ***/
/***                                                                       ***/
/*** Demonstrates how to keep track of the server using a "heartbeat".  If ***/
/*** the heartbeat is lost, the connection can be reestablished and the    ***/
/*** session resumed.                                                      ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/tcp.h>

#define DELAY	5 /*seconds*/

int serverfd, got_reply=1;

/*---------------------------------------------------------------------*/
/*--- sig_handler - if the single is OOB, set flag.  If ALARM, send ---*/
/*--- heartbeat.                                                    ---*/
/*---------------------------------------------------------------------*/
void sig_handler(int signum)
{
	if ( signum == SIGURG )
	{   char c;
		recv(serverfd, &c, sizeof(c), MSG_OOB);
		got_reply = ( c == 'Y' );			  /* Got reply */
		fprintf(stderr,"[got it]");
	}
	else if ( signum == SIGALRM )
		if ( got_reply )
		{
			send(serverfd, "?", 1, MSG_OOB);	 /* Alive?? */
			alarm(DELAY);				   /* Wait a while */
			got_reply = 0;
		}
		else
			fprintf(stderr, "Lost connection to server!");
}

/*---------------------------------------------------------------------*/
/*--- main - set up client and begin the heartbeat.                 ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{	struct sockaddr_in addr;
	struct sigaction act;
	int bytes;
	char line[100];

	if ( count != 3 )
	{
		printf("usage: %s <addr> <port>\n", strings[0]);
		exit(0);
	}
	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGURG, &act, 0);
	sigaction(SIGALRM, &act, 0);

	serverfd = socket(PF_INET, SOCK_STREAM, 0);
	/*---claim SIGIO/SIGURG signals---*/
	if ( fcntl(serverfd, F_SETOWN, getpid()) != 0 )
		perror("Can't claim SIGURG and SIGIO");
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(strings[2]));
	inet_aton(strings[1], &addr.sin_addr);
	if ( connect(serverfd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{
		alarm(DELAY);
		do
		{
			gets(line);
printf("send [%s]\n", line);
			send(serverfd, line, strlen(line), 0);
			bytes = recv(serverfd, line, sizeof(line), 0);
		}
		while ( bytes > 0 );
	}
	else
		perror("connect failed");
	close(serverfd);
	return 0;
}

