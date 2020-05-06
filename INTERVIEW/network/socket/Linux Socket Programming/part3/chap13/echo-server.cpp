/* echo-server.cpp
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
/*** echo-server.cpp                                                       ***/
/***                                                                       ***/
/*** Demonstrate creating a SocketServer object.                           ***/
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "socket.h"

TextMessage welcome("Welcome to the EchoServer(TCP)\n");

void Echoer(const Socket& client)
{
	try
	{
		TextMessage msg(1024);
		client.Send(welcome);
		do
		{
			client.Receive(msg);
			printf("bytes=%d: ", msg.GetSize());
			printf("%s", msg.GetBuffer());
			client.Send(msg);
		}
		while ( msg.GetSize() > 0  &&  strcmp(msg.GetBuffer(), "bye\n") != 0 );
	}
	catch (Exception& err)
	{
		err.PrintException();
	}
}

int main(int count, char *strings[])
{
	if ( count != 2 )
	{
		printf("usage: %s <port>\n", strings[0]);
		exit(1);
	}

	int port = atoi(strings[1]);
	if ( port <= 0 )
	{
		printf("Illegal port value: must be >0\n");
		exit(-1);
	}

	try
	{
		SocketServer server(port);
		do
			server.Accept(Echoer);
		while ( 1 );
	}
	catch (Exception& err)
	{
		err.PrintException();
	}
	catch (...)
	{
		fprintf(stderr, "Unknown error\n");
	}
	return 0;
}
