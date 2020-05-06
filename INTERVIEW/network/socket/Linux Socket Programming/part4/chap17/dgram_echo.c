/* dgram_echo.c
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
/*** dgram_echo.c                                                          ***/
/***                                                                       ***/
/*** Demonstrate a single-task datagram echo (intended on the same host).  ***/
/*****************************************************************************/

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <sched.h>
#include <sys/signal.h>
#include <time.h>

/*---------------------------------------------------------------------*/
/*--- panic - display error and die.                                ---*/
/*---------------------------------------------------------------------*/
void panic(char* msg, ...)
{	va_list ap;

	va_start(ap, msg);
	vprintf(msg, ap);
	perror("errno=");
	va_end(ap);
	abort();
}

/*---------------------------------------------------------------------*/
/*--- strtrim - remove spaces before and after string               ---*/
/*---------------------------------------------------------------------*/
char* strtrim(char *str)
{	char *tail;

	tail = str+strlen(str)-1;
	while ( tail > str  &&  *tail <= ' ' )
		*tail-- = 0;
	return str;
}

/*---------------------------------------------------------------------*/
/*--- main - set up socket, wait for message and echo it back.      ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{	int sd, port;
	struct sockaddr_in addr;
	char buffer[1024];
	void *stack;

	if ( count == 2 )
		port = atoi(strings[1]);
	else
	{
		printf("usage: %s <listening-port>\n", strings[0]);
		return 0;
	}
	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if ( sd < 0 )
		panic("socket failed");
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		panic("bind failed");
	do
	{	int len = sizeof(addr);
		time_t t;

		bzero(buffer, sizeof(buffer));
		recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len);
		printf("%s:%d \"%s\"\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buffer);
		strncat(buffer, " (", sizeof(buffer)-1);
		time(&t);
		strncat(buffer, strtrim(ctime(&t)), sizeof(buffer)-1);
		strncat(buffer, ")", sizeof(buffer)-1);
		if ( sendto(sd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&addr, len) < 0 )
			perror("sendto");
	}
	while ( strcmp(buffer, "bye") != 0 );
	close(sd);
	return 0;
}

