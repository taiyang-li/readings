/* mcast_client.c
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
/*** mcast_client.c                                                        ***/
/***                                                                       ***/
/*** Demonstrates how to join multicast group and send messages.           ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <sched.h>
#include <sys/signal.h>

#define DEFAULT_PORT	9999

/*---------------------------------------------------------------------*/
/*--- panic - print message and die.                                ---*/
/*---------------------------------------------------------------------*/
void panic(char* msg, ...)
{	va_list ap;

	va_start(ap, msg);
	vprintf(msg, ap);
	perror("errno");
	va_end(ap);
	abort();
}

/*---------------------------------------------------------------------*/
/*--- strtrim - remove spaces around string.                        ---*/
/*---------------------------------------------------------------------*/
char* strtrim(char *str)
{	char *tail;

	tail = str+strlen(str)-1;
	while ( tail > str  &&  *tail <= ' ' )
		*tail-- = 0;
	return str;
}

/*---------------------------------------------------------------------*/
/*--- Receiver - listens for and collects multicast packets.        ---*/
/*---------------------------------------------------------------------*/
int Receiver(int sd)
{	char buffer[1024];
	struct sockaddr_in addr;

	do
	{	int len = sizeof(addr);

		if ( recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len) > 0 )
			printf("Got %s:%d \"%s\"\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buffer);
		else
			perror("recvfrom");
	}
	while ( strcmp(buffer, "bye\n") != 0 );
	fprintf(stderr, "clone exiting\n");
	exit(0);
}

/*---------------------------------------------------------------------*/
/*--- main - creates multicast-capable socket and sends test packets---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{	const int on=1;
	int sd, port;
	struct ip_mreq mreq;
	struct sockaddr_in addr;
	char buffer[1024];
	void *stack;

	if ( count < 3  ||  count > 4)
	{
		printf("usage: %s [<listening-port>] <dest-addr> <dest-port>\n", strings[0]);
		return 0;
	}
	if ( count == 4 )
	{
		port = atoi(strings[1]);
		strings++;
	}
	else
		port = DEFAULT_PORT;

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if ( sd < 0 )
		panic("socket failed");

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		panic("bind failed");

	if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != 0 )
		panic("Can't reuse address/ports");
	if ( inet_aton(strings[1], &mreq.imr_multiaddr) == 0 )
		panic("address (%s) bad", strings[1]);
	mreq.imr_interface.s_addr = INADDR_ANY;
	if ( setsockopt(sd, SOL_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
		panic("Join multicast failed");

	addr.sin_port = htons(atoi(strings[2]));
	if ( inet_aton(strings[1], &addr.sin_addr) == 0 )
		panic("inet_aton failed (%s)", strings[1]);

	if ( fork() )
		Receiver(sd);
	else
		shutdown(sd, 0);	/* close the input channel */
	do
	{
		fgets(buffer, sizeof(buffer), stdin);
		strtrim(buffer);
		if ( sendto(sd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
			perror("sendto");
	}
	while ( strcmp(buffer, "bye") != 0 );
	wait(0);
	close(sd);
	return 0;
}

