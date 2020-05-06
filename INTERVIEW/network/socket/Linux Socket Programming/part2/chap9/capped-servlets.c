/* capped-servlets.c
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
/*** capped-servlets.c                                                     ***/
/***                                                                       ***/
/*** Simple service offering with a maximum servlet count.                 ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <sys/wait.h>

#define MAXCLIENTS	20
int ChildCount=0;

/*--------------------------------------------------------------------*/
/*--- Signal capture: SIGCHLD                                      ---*/
/*--------------------------------------------------------------------*/
void sig_child(int sig)
{
	while ( waitpid(-1, 0, WNOHANG) > 0 )
		ChildCount--;
}

/*--------------------------------------------------------------------*/
/*--- Service - present service to connection (echo-er)            ---*/
/*--------------------------------------------------------------------*/
void child(int client)
{	char buffer[1024];
	int bytes;

	do
	{
		bytes = recv(client, buffer, sizeof(buffer), 0);
		if ( bytes > 0 )
			send(client, buffer, bytes, 0);
	}
	while ( bytes > 0  &&  strncmp(buffer, "bye\r", 4) != 0 );
	close(client);
	exit(0);
}

/*--------------------------------------------------------------------*/
/*--- main - create socket, create processes up to max             ---*/
/*--------------------------------------------------------------------*/
int main()
{	int sd;
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{
		listen(sd, 20);
		for (;;)
		{   int client, len=sizeof(addr);
			while ( ChildCount >= MAXCLIENTS )
				sleep(1);  /*---You could "sched_yield()" instead---*/
			client = accept(sd, (struct sockaddr*)&addr, &len);
			if ( client > 0 )
			{   int pid;

				if ( (pid = fork()) == 0 )
				{/*---CHILD---*/
					close(sd);
					child(client); /*---Serve the new client---*/
				}
				else if ( pid > 0 )
				{/*---PARENT---*/
					ChildCount++;
					close(client);
				}
				else
					perror("fork() failed");
			}
		}
	}
	else
		perror("bind() failed");
	return 0;
}

