/* sigpipe-server.c
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
/*** sigpipe-server.c                                                      ***/
/***                                                                       ***/
/*** Demonstrates how to generate a SIGPIPE error with a socket.           ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>

/*---------------------------------------------------------------------*/
/*--- sig_pipe - SIGPIPE                                            ---*/
/*---------------------------------------------------------------------*/
void sig_pipe(int signum)
{
	printf("got it!\n");
	signal(SIGPIPE, sig_pipe);
}

/*---------------------------------------------------------------------*/
/*--- main - allow client to connect and then terminate.            ---*/
/*---------------------------------------------------------------------*/
main()
{	struct sockaddr_in addr;
	int sd, byte_count, addr_size;

	signal(SIGPIPE, sig_pipe);
	if ( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		abort();
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		perror("Bind");
		abort();
	}
	if ( listen(sd, 20) != 0 )
	{
		perror("Listen");
		abort();
	}
	while (1)
	{	int client;
		char buffer[1024];
		addr_size = sizeof(addr);
		client = accept(sd, (struct sockaddr*)&addr, &addr_size);
		printf("Connected: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		recv(client, buffer, 4, 0);
		close(client);
	}
	close(sd);
}

