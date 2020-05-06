/* test-port-client.c
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
/*** test-port-client.c                                                    ***/
/***                                                                       ***/
/*****************************************************************************/

/**************************************************************************
*	This is a port-read client.  It will accept any IP address and port
*	number on the commandline, connect to the server, send the message
*	(if any defined), read the reply, and close.
**************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <errno.h>

#define MAXBUF	1024

int main(int Count, char *Strings[])
{	int sockfd, bytes_read;
	struct sockaddr_in dest;
	char buffer[MAXBUF];

	/*---Make sure we have the right number of parameters---*/
	if ( Count < 3  ||  Count > 4 )
	{
		fprintf(stderr, "usage: %s <IP-addr> <port> [<send-msg>]\n", Strings[0]);
		exit(0);
	}

	/*---Create socket for streaming---*/
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

	/*---Initialize server address/port struct---*/
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	if ( inet_addr(Strings[1], &dest.sin_addr.s_addr) == 0 )
	{
		perror(Strings[1]);
		exit(errno);
	}
	dest.sin_port = htons(atoi(Strings[2]));

	/*---Connect to server---*/
	if ( connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0 )
	{
		perror("Connect");
		exit(errno);
	}

	/*---If there is a message to send server, send it with a '\n' (newline)---*/
	if ( Count == 4 )
	{
		sprintf(buffer, "%s\n", Strings[3]);
		send(sockfd, buffer, strlen(buffer), 0);
	}

	/*---While there's data, read and print it---*/
	do
	{
		bzero(buffer, MAXBUF);
		bytes_read = recv(sockfd, buffer, MAXBUF, 0);
		if ( bytes_read > 0 )
			printf("%s", buffer);
	}
	while ( bytes_read > 0 );

	/*---Clean up---*/
	close(sockfd);
	return 0;
}

