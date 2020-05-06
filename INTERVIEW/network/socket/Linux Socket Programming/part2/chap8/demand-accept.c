/* demand-accept.c
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
/*** demand-accept.c                                                       ***/
/***                                                                       ***/
/*** Accept connections based on signal demand.  When a connection is made,***/
/*** a SIGIO  is raised and the process stops to handle it.  The handler   ***/
/*** connects to the client.  The main program could be processing other   ***/
/*** tasks when these connections arrive.                                  ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <signal.h>
#include <fcntl.h>

void PANIC(char* msg);
#define PANIC(msg) { perror(msg); abort(); }

int sd;

/*--------------------------------------------------------------------*/
/*--- Signal capture: SIGIO - connect to client.                   ---*/
/*--------------------------------------------------------------------*/
void sig_io(int sig)
{	int client;

	client = accept(sd, 0, 0);
	send(client, "hello\ngoodbye!\n\n", 16, 0);
	close(client);
}

/*--------------------------------------------------------------------*/
/*--- main - set up asynchronous connections and wait              ---*/
/*--------------------------------------------------------------------*/
int main()
{	int flag=64;
	struct sockaddr_in addr;
	struct sigaction act;

	bzero(&act, sizeof(act));
	act.sa_handler = sig_io;
	if ( sigaction(SIGIO, &act, 0) < 0 )
		PANIC("SigAction");
	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		PANIC("bind");
	if ( listen(sd, 20) != 0 )
		PANIC("listen");
	if ( fcntl(sd, F_SETFL, O_ASYNC | O_NONBLOCK) < 0 )
		PANIC("async & nonblocking");
	if ( fcntl(sd, F_SETOWN, getpid()) < 0 )
		PANIC("setown");
	while (1)
		sleep(5);
	return 0;
}

