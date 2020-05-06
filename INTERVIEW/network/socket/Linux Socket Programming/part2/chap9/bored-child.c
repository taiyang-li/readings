/* bored-child.c
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
/*** bored-child.c                                                         ***/
/***                                                                       ***/
/*** This server example creates servlets up to a maximum amount.  Extra   ***/
/*** servlets will die after a while.                                      ***/
/*****************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sched.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <resolv.h>

void PANIC(char *msg);
#define PANIC(msg)  {perror(msg);abort();}

#define DEF_SERVLETS    5
#define DEF_TIMEOUT     10
#define BOREDOM         55
#define CHECK_DELAY     5

int ServletCnt=0;
int ServletMax=DEF_SERVLETS;
int Timeout=0;
struct sigaction act;
struct sockaddr_in addr;

/*--------------------------------------------------------------------*/
/*--- Signal capture: SIGCHLD & SIGALRM                            ---*/
/*--------------------------------------------------------------------*/
void sig_handler(int sig)
{   int status;

    switch ( sig )
    {
        case SIGCHLD:
            while ( waitpid(-1, &status, WNOHANG) > 0 )
            	if ( WIFEXITED(status)  &&  WEXITSTATUS(status) == BOREDOM+1 )
                	ServletCnt--;
            break;
        case SIGALRM:
            fprintf(stderr, "timeout\n");
            break;
    }
}

/*--------------------------------------------------------------------*/
/*--- Service - provide the child the desired service              ---*/
/*--------------------------------------------------------------------*/
void Service(int client)
{   char buffer[1024];

    do
        send(client, buffer, recv(client, buffer, sizeof(buffer), 0), 0);
    while ( strncmp(buffer, "bye\r", 4) != 0 );
}

/*--------------------------------------------------------------------*/
/*--- Servlet - provide a connection point for a service.          ---*/
/*--------------------------------------------------------------------*/
void Servlet(int sd, int timeout)
{   int hasAlarm=0;

    if ( timeout > 0 )
    {
        bzero(&act, sizeof(act));
        act.sa_handler = sig_handler;
        hasAlarm = ( sigaction(SIGALRM, &act, 0) == 0 );
    }
    for (;;)
    {   int client, addlen=sizeof(addr);

        if ( hasAlarm  &&  timeout > 0 )
            alarm(timeout);
        client = accept(sd, (struct sockaddr*)&addr, &addlen);
        if ( client > 0 )
            Service(client);
        else
        {
            perror("accept");
            if ( client == EINTR )
                exit(0);
        }
    }
}

/*--------------------------------------------------------------------*/
/*--- main - Create socket & spawn processes.                      ---*/
/*--------------------------------------------------------------------*/
int main(int count, char *strings[])
{   int sd;

    if ( count != 3 )
    {
        printf("Usage: %s <port> <min-servlets>", strings[0]);
        exit(0);
	}
    bzero(&act, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = SA_NOCLDSTOP;
    if ( sigaction(SIGCHLD, &act, 0) != 0 )
        PANIC("sigaction() failed");
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if ( sd < 0 )
        PANIC("socket() failed");
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(strings[1]));
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
        PANIC("bind() failed");
    if ( listen(sd, 20) != 0 )
        PANIC("listen() failed");
    for (;;)
    {
        if ( ServletCnt >= DEF_SERVLETS )
            Timeout = DEF_TIMEOUT;
        if ( ServletCnt < ServletMax )
        {   int pid;

            fprintf(stderr, "New servlet\n");
            if ( (pid = fork()) == 0 )
                Servlet(sd, Timeout);
            else if ( pid > 0 )
                ServletCnt++;
            else
                perror("fork() failed");
        }
        else
            sleep(CHECK_DELAY);
    }
    return 0;
}

