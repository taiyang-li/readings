/* upd-server.c
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
/*** upd-server.c                                                          ***/
/***                                                                       ***/
/*** Create a datagram server that waits for client messages (which it     ***/
/*** echoes back).                                                         ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

#define DEFAULT_PORT	9999

int main(int count, char *strings[])
{	int sd;
	int port=DEFAULT_PORT;
	struct sockaddr_in addr;
	char buffer[1024];

	if ( count != 2 )
		printf("usage: %s <port>\n...Using default port (%d).\n", strings[0], port);
	else
		port = atoi(strings[1]);
	sd = socket(PF_INET, SOCK_DGRAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("bind");
	while (1)
	{	int bytes, addr_len=sizeof(addr);

		bytes = recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
		printf("msg from %s:%d (%d bytes)\n", inet_ntoa(addr.sin_addr),
						ntohs(addr.sin_port), bytes);
		sendto(sd, buffer, bytes, 0, (struct sockaddr*)&addr, sizeof(addr));
	}
	close(sd);
}

