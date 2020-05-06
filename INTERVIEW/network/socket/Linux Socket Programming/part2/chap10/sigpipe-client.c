/* sigpipe-client.c
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
/*** sigpipe-client.c                                                      ***/
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
/*--- main - force a SIGPIPE error by connecting to an echo server  ---*/
/*--- and sending data while the server just terminates the         ---*/
/*--- connection.                                                   ---*/
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
	if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 )
	{
		perror("127.0.0.1");
		abort();
	}
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		perror("Bind");
		abort();
	}
	if ( send(sd, "this is a test", 17, 0) < 0 )
		perror("send");
	sleep(1);
	if ( send(sd, "this is a test", 17, 0) < 0 )
		perror("send");
	close(sd);
}

