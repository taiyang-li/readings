/* mytrace.c
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
/*** mytrace.c                                                             ***/
/***                                                                       ***/
/*** Using the ICMP echo protocol, carefully track the messages down to    ***/
/*** the destined host.  The TTL is incremented for every reply back.      ***/
/*** Note: if any router does not reply, the program waits indefinitely.   ***/
/*****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#define PACKETSIZE	64
struct packet
{
	struct icmphdr hdr;
	char msg[PACKETSIZE-sizeof(struct icmphdr)];
};

int pid=-1;
struct protoent *proto=NULL;

/*---------------------------------------------------------------------*/
/*--- checksum - standard 1s complement checksum                    ---*/
/*---------------------------------------------------------------------*/
unsigned short checksum(void *b, int len)
{	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

/*---------------------------------------------------------------------*/
/*--- traceroute - incrementally try to reach the destination       ---*/
/*---------------------------------------------------------------------*/
void traceroute(struct sockaddr_in *addr)
{	const int yes=1;
	int TTL=0;
	int i, sd, cnt=1;
	struct packet pckt;
	unsigned char buf[1024];
	struct sockaddr_in r_addr;

	sd = socket(PF_INET, SOCK_RAW, proto->p_proto);
	if ( sd < 0 )
	{
		perror("socket");
		return;
	}
	if ( setsockopt(sd, SOL_IP, SO_ERROR, &yes, sizeof(yes)) != 0 )
		perror("Set getting socket errors");
	do
	{	int len=sizeof(r_addr);
		struct iphdr *ip;

		TTL++;
		if ( setsockopt(sd, SOL_IP, IP_TTL, &TTL, sizeof(TTL)) != 0)
			perror("Set TTL option");
		bzero(&pckt, sizeof(pckt));
		pckt.hdr.type = ICMP_ECHO;
		pckt.hdr.un.echo.id = pid;
		for ( i = 0; i < sizeof(pckt.msg)-1; i++ )
			pckt.msg[i] = i+'0';
		pckt.msg[i] = 0;
		pckt.hdr.un.echo.sequence = cnt++;
		pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
		if ( sendto(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)addr, sizeof(*addr)) <= 0 )
			perror("sendto");
		if ( recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr*)&r_addr, &len) > 0 )
		{ 	struct hostent *hname;
			ip = (void*)buf;
			printf("Host #%d: %s \n", cnt-1, inet_ntoa(ip->saddr));
			hname = gethostbyaddr((void*)&r_addr, len, r_addr.sin_family);
			if ( hname != NULL )
 				printf("(%s)\n", hname->h_name);
			else
				perror("Name");
 		}
		else
			perror("recvfrom");
	}
	while ( r_addr.sin_addr.s_addr != addr->sin_addr.s_addr );
	close(sd);
}

/*---------------------------------------------------------------------*/
/*--- main - set up port and run.                                   ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *strings[])
{	struct hostent *hname;
	struct sockaddr_in addr;

	if ( count != 2 )
	{
		printf("usage: %s <addr>\n", strings[0]);
		exit(0);
	}
	if ( count > 1 )
	{
		pid = getpid();
		proto = getprotobyname("ICMP");
		hname = gethostbyname(strings[1]);
		bzero(&addr, sizeof(addr));
		addr.sin_family = hname->h_addrtype;
		addr.sin_port = 0;
		addr.sin_addr.s_addr = *(long*)hname->h_addr;
		traceroute(&addr);
	}
	else
		printf("usage: myping <hostname>\n");
	return 0;
}

