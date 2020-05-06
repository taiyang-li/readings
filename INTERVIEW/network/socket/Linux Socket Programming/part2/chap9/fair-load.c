/* fair-load.c
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
/*** fair-load.c                                                           ***/
/***                                                                       ***/
/*** This demonstrates how to balance the load of connections across       ***/
/*** several servlet-threads.                                              ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <resolv.h>
#include <sys/poll.h>

#define MAXTHREADS	10
#define MAXRANGE	10
#define MAXFDs		(MAXTHREADS*MAXRANGE)

int fd_count=0;
int starts[MAXTHREADS];
struct pollfd fds[MAXFDs]; /* cleared with bzero() */

/*--------------------------------------------------------------------*/
/*--- Servlet - process incoming requests                          ---*/
/*--------------------------------------------------------------------*/
void *Servlet(void *init)
{   int start = *(int*)init; /* get the fd-range start */
	for (;;)
	{   int result;
		/* wait for only 0.5 second */
		if ( (result = poll(fds+start, MAXRANGE, 500)) > 0 )
		{   int i;
			for ( i = 0; i < MAXRANGE; i++ )
			{
				/* If input ready, echo it back */
				if ( fds[i].revents & POLLIN )
				{	char buffer[1024];
					int bytes;

					do
					{
						bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
						if ( bytes > 0 )
							send(fds[i].fd, buffer, bytes, 0);
					}
					while ( bytes > 0 );
				}

				/* if closed on other end, close here */
				else if ( fds[i].revents & POLLHUP )
				{
					close(fds[i].fd);
					bzero(&fds[i], sizeof(fds[i]));
				}
			}
		}
		else if ( result < 0 )
			perror("poll() error");
	}
	return 0;
}

/*--------------------------------------------------------------------*/
/*--- main - set up server and redirect connections to servlets    ---*/
/*--------------------------------------------------------------------*/
int main()
{   int sd;
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{	int i;
		pthread_t thread;

		for ( i = 0; i < MAXTHREADS; i++ )
		{
			starts[i] = i*MAXRANGE;
			if ( pthread_create(&thread, 0, Servlet, starts+i) == 0 )
				pthread_detach(thread);
			else
				perror("pthread_create() failed");
		}
		for (;;)
		{   int i;
			/*--- Find an available slot before accepting conn. ---*/
			for ( i = 0; i < fd_count; i++ )
				if ( fds[i].events == 0 )
					break;
			if ( i == fd_count  &&  fd_count < MAXFDs )
				fd_count++;
			/*---If you have an available slot, accept connection---*/
			if ( i < fd_count )
			{
				fds[i].fd = accept(sd, 0, 0);
				fds[i].events = POLLIN | POLLHUP;
			}
			else /* otherwise, yield for a little while */
				sleep(1); /* or, some yielding delay */
		}
	}
	else
		perror("bind() failed");
	return 0;
}

