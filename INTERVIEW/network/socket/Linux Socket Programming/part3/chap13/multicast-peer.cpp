/* multicast-peer.cpp
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
/*** multicast-peer.cpp                                                    ***/
/***                                                                       ***/
/*** Demonstrate how to create and work with a MessageGroup (multicast)    ***/
/*** object.                                                               ***/
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include "socket.h"

#define FALSE	0
#define TRUE	1

bool done=FALSE;

/*---------------------------------------------------------------------*/
/*--- sigchild - SIGCHLD                                            ---*/
/*---------------------------------------------------------------------*/
void sigchild(int sig)
{
	wait(0);
	done=TRUE;
}

/*---------------------------------------------------------------------*/
/*--- receiver - catch all multicast messages                       ---*/
/*---------------------------------------------------------------------*/
void receiver(Socket* socket)
{	HostAddress peer;
	TextMessage msg(1024);

	try
	{
		do
		{
			socket->Receive(peer, msg);
			printf("[%s] msg=%s", peer.GetHost(), msg.GetBuffer());
		}
		while ( strcmp(msg.GetBuffer(), "bye\n") != 0 );
	}
	catch (Exception& err)
	{
		printf("[CHILD]");
		err.PrintException();
	}
	catch (...)
	{
		fprintf(stderr, "Unknown error\n");
	}
	exit(0);
}

/*---------------------------------------------------------------------*/
/*--- main - create MessageGroup object and fork into a sender and  ---*/
/*--- receiver.                                                     ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{
	signal(SIGCHLD, sigchild);
	if ( count != 3 )
	{
		printf("usage: %s <addr:port> <group>\n", strings[0]);
		exit(1);
	}
	HostAddress addr(strings[1]);
	HostAddress group(strings[2]);
	group.SetPort(addr.GetPort());

	try
	{
		MessageGroup *channel = new MessageGroup(addr);
		channel->Join(group);
		if ( !fork() )
			receiver(channel);
		channel->CloseInput();
		TextMessage msg(1024);
		do
		{
			char line[100];
			fgets(line, sizeof(line), stdin);
			msg = line;
			channel->Send(group, msg);
		}
		while ( !done );
		delete channel;
	}
	catch (Exception& err)
	{
		printf("[PARENT]");
		err.PrintException();
	}
	catch (...)
	{
		fprintf(stderr, "Unknown error\n");
	}
	return 0;
}
