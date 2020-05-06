/* serverls.c
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
/*** serverls.c                                                            ***/
/***                                                                       ***/
/*** This is an example of a server that links clients to external         ***/
/*** programs with the exec() call.  Of course, the external program does  ***/
/*** not know about the socket, so the all I/O has to be redirected to     ***/
/*** stdin/stdout. The redirection requires the program to fork a new      ***/
/*** process, so that the server can still talk to its own stdin/stdout.   ***/
/*****************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>

#define MY_PORT		9999

int main()
{	int sd;
	struct sockaddr_in self;

	/*---Create new socket---*/
	if ( (sd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}
/*	if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, 0, 0) < 0 ) perror("SocketOpt");*/

	/*---Initialize own server address---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_addr.s_addr = INADDR_ANY;
	self.sin_port = htons(MY_PORT);

	/*---Give the socket a "name" (set the IP and Port addresses)---*/
	if ( bind(sd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("Bind");
		abort();
	}

	/*---Make the socket a "listening socket"---*/
	if ( listen(sd, 20) != 0 )
	{
		perror("Listen");
		abort();
	}

	/*---Forever...---*/
	while (1)
	{	static int client;
		int sd_copy, size;
		struct sockaddr_in client_info;

		/*---Accept client connection (creates a new communication port)---*/
		size = sizeof(client_info);
		client = accept(sd, (struct sockaddr*)&client_info, &size);
		printf("Connected: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

		/*---Create child task to handle service---*/
		if ( fork() != 0 )
		{
/*Parent*/	/*---The parent doesn't need the child's data connection---*/
			if ( close(client) < 0 )
				perror("Close");
		}
		else
		{
/*Child*/	/*---Child doesn't need access to request connection---*/
			if ( close(sd) < 0 )
				perror("Client--close listener");

			/*---Map stdin, stdout and stderr to the data connection---*/
			if ( dup2(client, 0) < 0 )
				perror("Dup stdin");
			if ( dup2(client, 1) < 0 )
				perror("Dup stdout");
			if ( dup2(client, 2) < 0 )
				perror("Dup stderr");

			/*---Call external program---*/
			execl("/bin/ls", "/bin/ls", "-al", "/sbin", 0);
		}
	}

	/*---Clean up (should never get here)---*/
	close(sd);
	return 0;
}

