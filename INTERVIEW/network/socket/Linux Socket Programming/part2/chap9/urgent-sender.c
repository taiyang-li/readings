/* urgent-sender.c
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
/*** urgent-sender.c                                                       ***/
/***                                                                       ***/
/*** Demonstrate the use of priority TCP (Out-Of-Band) traffic.            ***/
/*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>

int main()
{	int sockfd;
	struct sockaddr_in addr;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("127.0.0.1", &addr.sin_addr);
	if ( connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("connect");
	printf("bytes written=%d (OOB)\n", send(sockfd, "A", 1, MSG_OOB));
	sleep(1);
	printf("bytes written=%d (normal)\n", send(sockfd, "ABCDE", 6, 0));
	sleep(5);
	printf("bytes written=%d (OOB)\n", send(sockfd, "B", 1, MSG_OOB));
	sleep(1);
	printf("bytes written=%d (normal)\n", send(sockfd, "12345678", 9, 0));
	sleep(5);
	close(sockfd);
	return 0;
}

