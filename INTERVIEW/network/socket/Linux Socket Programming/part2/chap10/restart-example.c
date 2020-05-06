/* restart-example.c
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
/*** restart-example.c                                                     ***/
/***                                                                       ***/
/*** Demonstrates how to restart the server by capturing the SIGHUP signal ***/
/*** Be careful -- this will not work all the time.                        ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int isfirst;
char **command_args;

void sig_hangup(int signum)
{
	if ( isfirst )
	{
		isfirst = 0;
		fprintf(stderr, "Parent died\n");
	}
	else				/* Restart! */
	{
		fprintf(stderr, "Restarting...\n");
		/*** Kill all existing child processes ***/
		execv(command_args[0], command_args);
		fprintf(stderr, "Could not restart!!!\n");
		abort();
	}
}

void child(void)
{	struct sigaction act;

	bzero(&act, sizeof(act));
	act.sa_handler = sig_hangup;
	act.sa_flags = SA_RESTART;
/*	if ( sigaction(SIGHUP, &act, 0) != 0 )
		perror("Can't capture SIGHUP");*/
	for (;;)
	{
		fprintf(stderr, "[pid=%d] I'm still here\n", getpid());
		sleep(1);
	}
	exit(0);
}

int main(int count, char *strings[])
{
	isfirst = 1;
	command_args = strings;
	if ( fork() == 0 )
		child();
	sleep(1);
	return 0;
}

