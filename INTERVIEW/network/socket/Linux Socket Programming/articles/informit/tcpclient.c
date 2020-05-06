/* tcpclient.c
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
/*** tcpclient.c                                                           ***/
/***                                                                       ***/
/*** Demonstrate an TCP client.                                            ***/
/*****************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netdb.h>

void panic(char *msg);
#define panic(m)	{perror(m); abort();}
/****************************************************************************/
/*** This program opens a connection to a server using either a port or a ***/
/*** service.  Once open, it sends the message from the command line.     ***/
/*** some protocols (like HTTP) require a couple newlines at the end of   ***/
/*** the message.                                                         ***/
/*** Compile and try 'tcpclient lwn.net http "GET / HTTP/1.0" '.          ***/
/****************************************************************************/
int main(int count, char *args[])
{	struct hostent* host;
	struct sockaddr_in addr;
	int sd, port;

	if ( count != 4 )
	{
		printf("usage: %s <servername> <protocol or portnum> <message>\n", args[0]);
		exit(0);
	}

	/*---Get server's IP and standard service connection--*/
	host = gethostbyname(args[1]);
	printf("Server %s has IP address = %s\n", args[1],
		inet_ntoa(*(long*)host->h_addr_list[0]));
	if ( !isdigit(args[2][0]) )
	{
		struct servent *srv = getservbyname(args[2], "tcp");
		if ( srv == NULL )
			panic(args[2]);
		printf("%s: port=%d\n", srv->s_name, ntohs(srv->s_port));
		port = srv->s_port;
	}
	else
		port = htons(atoi(args[2]));

	/*---Create socket and connect to server---*/
	sd = socket(PF_INET, SOCK_STREAM, 0);        /* create socket */
	if ( sd < 0 )
		panic("socket");
	memset(&addr, 0, sizeof(addr));       /* create & zero struct */
	addr.sin_family = AF_INET;        /* select internet protocol */
	addr.sin_port = port;                       /* set the port # */
	addr.sin_addr.s_addr = *(long*)(host->h_addr_list[0]);  /* set the addr */

	/*---If connection successful, send the message and read results---*/
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0)
	{	char s[200];
		FILE *fp = fdopen(sd, "r+");       /* convert into stream */

		fprintf(fp, args[3]);                     /* send request */
		fprintf(fp, "\n\n");                 /* add some newlines */
		fflush(fp);                          /* ensure it got out */
		while ( fgets(s, sizeof(s), fp) != 0 )/* while not EOF ...*/
			fputs(s, stdout);                /*... print the data */
		fclose(fp);                           /* close the socket */
	}
	else
		panic("connect");
}
