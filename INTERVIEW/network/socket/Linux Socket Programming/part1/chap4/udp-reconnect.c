/* udp-reconnect.c
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
/*** udp-reconnect.c                                                       ***/
/***                                                                       ***/
/*** Demonstrates reconnecting to a UDP server.                            ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

int main()
{	int sd;
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	char buffer[1024];

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("127.0.0.1", &addr.sin_addr);
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("connect 1");
	send(sd, "sean\n", 5, 0);
	bzero(buffer, sizeof(buffer));
	recv(sd, buffer, sizeof(buffer), 0);
	printf("%s\n", buffer);
	addr.sin_port = htons(10000);
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("connect 2");
	send(sd, "GET / HTTP/1.0\n\n", 16, 0);
	bzero(buffer, sizeof(buffer));
	recv(sd, buffer, sizeof(buffer), 0);
	printf("%s\n", buffer);
	close(sd);
}

