/* ttcp-server.c
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
/*** ttcp-server.c                                                         ***/
/***                                                                       ***/
/*** Test support for transaction-TCP (T/TCP).                             ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

#define DEFAULT_PORT	9999

void PANIC(char* msg);
#define PANIC(msg)	{perror(msg);abort();}

int main(int count, char *strings[])
{	int sd;
	int port=DEFAULT_PORT;
	struct sockaddr_in addr;

	if ( count != 2 )
		printf("usage: %s <portnum>\n...Using default port (%d).\n", strings[1], port);
	else
		port = atoi(strings[1]);
	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		PANIC("bind");
	if ( listen(sd, 20) != 0 )
		PANIC("listen");
	while (1)
	{	char buffer[1024];

		int client = accept(sd, 0, 0);
		printf("connected\n");
		send(client, buffer, recv(client, buffer, sizeof(buffer), 0), 0);
		close(client);
	}
	return 0;
}

