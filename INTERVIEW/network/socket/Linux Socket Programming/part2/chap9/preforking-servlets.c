/* preforking-servlets.c
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
/*** preforking-servlets.c                                                 ***/
/***                                                                       ***/
/*** Anticipate a certain number of connections to be made by creating the ***/
/*** servlets ahead of time.                                               ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include <resolv.h>

#define MAXPROCESSES	5

int ChildCount=0;

/*---------------------------------------------------------------------*/
/*--- sig_child - SIGCHLD                                           ---*/
/*---------------------------------------------------------------------*/
void sig_child(int sig)
{
	wait(0);
    ChildCount--;
}

/*---------------------------------------------------------------------*/
/*--- servlet - accept connection and process requests.             ---*/
/*---------------------------------------------------------------------*/
void servlet(int server)
{	int bytes;
	char buffer[1024];

	for (;;)
	{
		int client = accept(server, 0, 0);
		if ( client > 0 )
		{
			do
			{
				bytes = recv(client, buffer, sizeof(buffer), 0);
				if ( bytes > 0 )
					send(client, buffer, bytes, 0);
			}
			while ( bytes > 0  &&  strncmp("bye\r", buffer, 4) != 0 );
			close(client);
		}
		else
		{
			perror("accept()");
			getchar();
		}
	}
}

/*---------------------------------------------------------------------*/
/*--- main - set up server, start servlets and keep servelt count up---*/
/*---------------------------------------------------------------------*/
main(int count, char *strings[])
{   int sd, pid;
	struct sockaddr_in addr;
	struct sigaction act;

	if ( count != 2 )
	{
		printf("usage: %s <port>\n", strings[0]);
		exit(0);
	}
	bzero(&act, sizeof(act));
	act.sa_handler = sig_child;
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	if ( sigaction(SIGCHLD, &act, 0) != 0 )
		perror("sigaction()");
	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(strings[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0 )
	{
		listen(sd, 15);
	    for (;;)
    	{
        	if ( ChildCount < MAXPROCESSES )
	        {
    	        if ( (pid = fork()) == 0 ) /*---CHILD---*/
					servlet(sd);
    	        else if ( pid > 0 )        /*---PARENT---*/
        	        ChildCount++;
	            else                       /*---ERROR---*/
    	            perror("fork() failed");
        	}
	        else
    	        sleep(1); /*--- OR, sched_yield()---*/
	    }
	}
	else
		perror("bind()");
}

