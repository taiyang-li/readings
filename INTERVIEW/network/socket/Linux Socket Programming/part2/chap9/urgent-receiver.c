/* urgent-receiver.c
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
/*** urgent-receiver.c                                                     ***/
/***                                                                       ***/
/*** Demonstrate the use of priority TCP (Out-Of-Band) traffic.            ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <resolv.h>
#include <signal.h>

int client;

void sig_handler(int signum)
{	char urgent_msg;

	switch ( signum )
	{
		case SIGURG:
			recv(client, &urgent_msg, sizeof(urgent_msg), MSG_OOB);
			printf("OOB: %c\n", urgent_msg);
			break;
	}
}

int main()
{   int sockfd;
	int i, size=sizeof(i);
	char buffer[100];
	struct sigaction act;
	struct sockaddr_in addr;

	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	act.sa_flags = SA_RESTART;
	if ( sigaction(SIGURG, &act, 0) != 0 )
		perror("sigaction");
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("bind() failed");
	listen(sockfd, 20);
	client = accept(sockfd, 0, 0);
	if ( fcntl(client, F_SETOWN, getpid()) != 0 )
		perror("fcntl");
	while ( recv(client, buffer, sizeof(buffer), 0) > 0 )
		printf("normal: %s\n", buffer);
	close(client);
	close(sockfd);
	exit(0);
}

