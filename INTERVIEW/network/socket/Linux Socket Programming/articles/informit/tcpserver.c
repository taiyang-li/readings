/* tcpserver.c
 *
 * Copyright (c) 2001 Sean Walton and Macmillan Publishers.  Use may be in
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
/*** tcpserver.c                                                           ***/
/***                                                                       ***/
/*** Demonstrate an TCP server.                                            ***/
/*****************************************************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <pthread.h>
#include <netdb.h>

void panic(char *msg);
#define panic(m)	{perror(m); abort();}

/*****************************************************************************/
/*** This program creates a simple echo server: whatever you send it, it   ***/
/*** echoes the message back.                                              ***/
/*****************************************************************************/
void *servlet(void *arg)                    /* servlet thread */
{	FILE *fp = (FILE*)arg;            /* get & convert the data */
	char s[100];

	   /* proc client's requests */
	while (fgets(s, sizeof(s), fp) != 0  &&  strcmp(s, "bye\n") != 0)
	{
		printf("msg: %s", s);                  /* display message */
		fputs(s, fp);                             /* echo it back */
	}
	fclose(fp);                   /* close the client's channel */
	return 0;                           /* terminate the thread */
}

int main(int count, char *args[])
{	struct sockaddr_in addr;
	int sd, port;

	if ( count != 2 )
	{
		printf("usage: %s <protocol or portnum>\n", args[0]);
		exit(0);
	}

	/*---Get server's IP and standard service connection--*/
	if ( !isdigit(args[1][0]) )
	{
		struct servent *srv = getservbyname(args[1], "tcp");
		if ( srv == NULL )
			panic(args[1]);
		printf("%s: port=%d\n", srv->s_name, ntohs(srv->s_port));
		port = srv->s_port;
	}
	else
		port = htons(atoi(args[1]));

	/*--- create socket ---*/
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if ( sd < 0 )
		panic("socket");

	/*--- bind port/address to socket ---*/
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = INADDR_ANY;                   /* any interface */
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		panic("bind");

	/*--- make into listener with 10 slots ---*/
	if ( listen(sd, 10) != 0 )
		panic("listen")

	/*--- begin waiting for connections ---*/
	else
	{	int sd;
		pthread_t child;
		FILE *fp;

		while (1)                         /* process all incoming clients */
		{
			sd = accept(sd, 0, 0);     /* accept connection */
			fp = fdopen(sd, "r+");           /* convert into FILE* */
			pthread_create(&child, 0, servlet, fp);       /* start thread */
			pthread_detach(child);                      /* don't track it */
		}
	}
}
