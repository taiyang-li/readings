/* ttcp-client.c
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
/*** ttcp-client.c                                                         ***/
/***                                                                       ***/
/*** Test transaction-TCP (T/TCP) support.                                 ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

#define DEFAULT_PORT	9999

#ifndef TCP_NOPUSH
#error TCP_NOPUSH not defined
#endif
#ifndef MSG_FIN
#error MSG_FIN or MSG_EOF not defined
#endif

void PANIC(char *msg);
#define PANIC(msg)	{perror(msg);abort();}

/*---------------------------------------------------------------------*/
/*--- main - try to connect to a t/tcp server.                      ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{	int sd;
	int port=DEFAULT_PORT;
	char *host="127.0.0.1";
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	char buffer[1024];

	if ( count == 3 )
	{
		port = atoi(strings[2]);
		host = strings[1];
	}
	else
		printf("usage: %s <server's address> <server's port>\n...using default port (%d)\n", strings[0], port);
	sd = socket(PF_INET, SOCK_STREAM, 0);

	/*---Set destination address---*/
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host, &addr.sin_addr);

	/*---Send message using directed protocol---*/
	if ( sendto(sd, "sean\n", 5, 0, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
		PANIC("sendto");
	bzero(buffer, sizeof(buffer));

	/*---Get message using directed protocol---*/
	recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
	printf("%s\n", buffer);
	close(sd);
}

