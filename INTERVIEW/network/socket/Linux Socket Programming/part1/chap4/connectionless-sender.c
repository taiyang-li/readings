/* connectionless-sender.c
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
/*** connectionless-sender.c                                               ***/
/***                                                                       ***/
/*** Send UDP messages to peer-receiver.                                   ***/
/*****************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>

#define BUFSIZE		1024

int main(int Count, char *Strings[])
{	char buffer[BUFSIZE];
	struct sockaddr_in addr;
	int sd, addr_size;

	if ( Count != 2 )
	{
		printf("usage: %s <msg>\n", Strings[0]);
		exit(0);
	}
	if ( (sd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("Socket");
		abort();
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 )
	{
		perror("127.0.0.1");
		abort();
	}
	sendto(sd, Strings[1], strlen(Strings[1])+1, 0, (struct sockaddr*)&addr, sizeof(addr));
	bzero(buffer, BUFSIZE);
	addr_size = sizeof(addr);
	if ( recvfrom(sd, buffer, BUFSIZE, 0, (struct sockaddr*)&addr, &addr_size) < 0 )
		perror("server reply");
	else
		printf("Reply: %s:%d \"%s\"\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buffer);
	close(sd);
	return 0;
}

