/* connectionless-receiver.c
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
/*** connectionless-receiver.c                                             ***/
/***                                                                       ***/
/*** Receive UDP messages from the sending-peer.                           ***/
/*****************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>

#define BUFSIZE		1024

#include <ctype.h>
void alltoupper(char* s)
{
	while ( *s != 0 )
		*s++ = toupper(*s);
}

int main()
{	char buffer[BUFSIZE];
	struct sockaddr_in addr;
	int sd, addr_size, bytes_read;

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if ( sd < 0 )
	{
		perror("socket");
		abort();
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
	{
		perror("bind");
		abort();
	}
	do
	{
		bzero(buffer, BUFSIZE);
		addr_size = BUFSIZE;
		bytes_read = recvfrom(sd, buffer, BUFSIZE, 0, (struct sockaddr*)&addr, &addr_size);
		if ( bytes_read > 0 )
		{
			printf("Connect: %s:%d \"%s\"\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buffer);
			alltoupper(buffer);
			if ( sendto(sd, buffer, bytes_read, 0, (struct sockaddr*)&addr, addr_size) < 0 )
				perror("reply");
		}
		else
			perror("recvfrom");
	}
	while ( bytes_read > 0 );
	close(sd);
	return 0;
}

