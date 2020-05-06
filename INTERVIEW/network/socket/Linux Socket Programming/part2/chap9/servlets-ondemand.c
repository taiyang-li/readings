/* servlets-ondemand.c
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
/*** servlets-ondemand.c                                                   ***/
/***                                                                       ***/
/*** This creates as many servlets as connections demand.  This has        ***/
/*** significant limitations and can bring the host down.                  ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signum)
{
	while ( waitpid(-1, 0, WNOHANG) > 0 );
}

/*---------------------------------------------------------------------*/
/*--- child - process request.                                      ---*/
/*---------------------------------------------------------------------*/
void child(int clientfd)
{	int bytes;
	char buffer[4096];

	do
	{
		bytes = recv(clientfd, buffer, sizeof(buffer), 0);
		if ( bytes > 0 )
			send(clientfd, buffer, bytes, 0);
	}
	while ( bytes > 0 );
	close(clientfd);
	exit(0);
}

/*---------------------------------------------------------------------*/
/*--- main - set up server and create processes for each connection ---*/
/*---------------------------------------------------------------------*/
int main()
{	int connections=0;
	int sd;
	struct sockaddr_in addr;
	struct sigaction act;

	bzero(&act, sizeof(act));
	act.sa_handler = sig_child;
	act.sa_flags = SA_NOCLDSTOP|SA_RESTART;
	if ( sigaction(SIGCHLD, &act, 0) != 0 )
		perror("sigaction() failed");
	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{
		listen(sd, 20);
		for (;;)
		{	int client, len=sizeof(addr);

    		client = accept(sd, (struct sockaddr*)&addr, &len);
			printf("Connections=%d\r", ++connections);
    		if ( client > 0 )
    		{   int pid;

        		if ( (pid = fork()) == 0 )
        		{
            		close(sd);
            		child(client); /*---Serve the new client---*/
        		}
        		else if ( pid > 0 )
            		close(client);
        		else
            		perror("fork() failed");
    		}
		}
		close(sd);
	}
	else
		perror("bind() failed");
	return 0;
}

