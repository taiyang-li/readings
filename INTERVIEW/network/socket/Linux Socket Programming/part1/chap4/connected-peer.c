/* connected-peer.c
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
/*** connected-peer.c                                                      ***/
/***                                                                       ***/
/*** This program demonstrates how to use connect() on a UDP peer.         ***/
/*** Remember that you can implicitly disconnect from one peer and         ***/
/*** establish a new connection by simply calling connect() again with the ***/
/*** desired peer's address.                                               ***/
/*** This program can be used for both ends of the connection.  The peer-  ***/
/*** end that has a message is assumed to be the initiator.  If you run    ***/
/*** both peers without any message, you will get a deadlock.              ***/
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define MAXBUF		1024
#define	MY_PORT		9998
#define PEER_PORT	9999
#define MAXIP		16		/* XXX.XXX.XXX.XXX */

char buffer[MAXBUF];

/*--------------------------------------------------------------------*/
/* SetAddress                                                         */
/*                                                                    */
/* Fill Addr with info from XXX.XXX.XXX.XXX:XXXXX format.             */
/*--------------------------------------------------------------------*/
int SetAddress(char* Composite, struct sockaddr_in *Addr)
{	int i;
	char IPAddress[MAXIP];

	bzero(Addr, sizeof(*Addr));
	Addr->sin_family = AF_INET;
	for ( i = 0; Composite[i] != ':'  &&  Composite[i] != 0  &&  i < MAXIP; i++ )
		IPAddress[i] = Composite[i];
	IPAddress[i] = 0;
	if ( Composite[i] == ':' )
		Addr->sin_port = htons(atoi(Composite+i+1));
	else
		Addr->sin_port = 0;
	if ( *IPAddress == 0 )
	{
		Addr->sin_addr.s_addr = INADDR_ANY;
		return 0;
	}
	else
		return ( inet_aton(IPAddress, &Addr->sin_addr) == 0 );
}

/*--------------------------------------------------------------------*/
/* main                                                               */
/*                                                                    */
/* Open socket, connect and receive messages                          */
/*--------------------------------------------------------------------*/
int main(int Count, char *Strings[])
{	int sd;
	struct sockaddr_in addr;

	if ( Count < 3  ||  Count > 4 )
	{
		printf("usage: coupled-peer <my addr:port> <peer addr:port> [<msg>]\n");
		exit(0);
	}
	if ( (sd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}
	if ( SetAddress(Strings[1], &addr) != 0 )
	{
		perror(Strings[1]);
		exit(errno);
	}
	if ( bind(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 )
	{
		perror("Bind");
		exit(errno);
	}
	if ( SetAddress(Strings[2], &addr) != 0 )
	{
		perror(Strings[2]);
		exit(errno);
	}
	if ( connect(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 )
	{
		perror("Connect");
		exit(errno);
	}
	if ( Count == 4 )
		send(sd, Strings[3], strlen(Strings[3]), 0);
	while (1)
	{	int bytes_read;

		bzero(buffer, sizeof(buffer));
		bytes_read = recv(sd, buffer, sizeof(buffer), 0);
		if ( bytes_read > 0 )
		{
			printf("Msg: %s\n", buffer);
			sleep(1);
			send(sd, buffer, bytes_read, 0);
		}
	}
	close(sd);
	return 0;
}


