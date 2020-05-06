/* client_v6.c
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
/*** client_v6.c                                                           ***/
/***                                                                       ***/
/*** Demonstrate IPv6 connections.                                         ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdarg.h>

void panic(char* msg, ...)
{   va_list ap;

    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
    abort();
}

int main(int count, char *strings[])
{	int sd, portnum;
	struct sockaddr_in6 addr;
	char line[100];

    if ( count == 3 )
        portnum = atoi(strings[2]);
    else
        portnum = 9999;
	bzero(&addr, sizeof(addr));
	if ( (sd = socket(PF_INET6, SOCK_STREAM, 0)) < 0 )
		panic("socket");
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(portnum);
    if ( inet_pton(AF_INET6, strings[1], &addr.sin6_addr) == 0 )
		panic("inet_aton");
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		panic("connect6");
	do
	{
		fgets(line, sizeof(line), stdin);
		send(sd, line, strlen(line)+1, 0);
		recv(sd, line, sizeof(line), 0);
		printf("client=%s", line);
	}
	while ( strcmp(line, "bye\n") != 0 );
	close(sd);
}

