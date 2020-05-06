/* imagecaster.c
 *
 * Copyright (c) 2001 Sean Walton and Macmillan Publishers.  Use may be in
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
/*** imagecaster.c                                                         ***/
/***                                                                       ***/
/*** Demonstrate a UDP file server.                                        ***/
/*****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <resolv.h>
#include "imagecaster.h"

/*---------------------------------------------------------------------*/
/*--- transmit - assemble and send packet.                          ---*/
/*---------------------------------------------------------------------*/
void transmit(int sd, struct bfile *bfile)
{
	bfile->header.hash = 0;
	bfile->header.checksum = 0;
	bfile->header.hash = htonl(dx_hack_hash(bfile->buffer, ntohs(bfile->header.size)));
	bfile->header.checksum = htons(checksum(bfile, sizeof(bfile->header)+ntohs(bfile->header.size)));
	send(sd, bfile, sizeof(bfile->header)+ntohs(bfile->header.size), 0);
#ifdef DEBUG
	printf("Sent offset=%d size=%d (%d total bytes)\n", ntohl(bfile->header.offset),
		ntohs(bfile->header.size), sizeof(bfile->header)+ntohs(bfile->header.size));
#endif
}

/*---------------------------------------------------------------------*/
/*--- sender - take apart a file and send it piece by piece.        ---*/
/*---------------------------------------------------------------------*/
void sender(int sd, char* filename, u16 bufsize)
{	int fd;
	int offset, bytes;
	struct stat stat;
	struct bfile bfile;
	struct bfile_info finfo;

	if ( (fd = open(filename, O_RDONLY)) < 0 )
		panic(filename);
	if ( fstat(fd, &stat) < 0 )
		perror("fstat");
	memset(&finfo, 0, sizeof(finfo));
	if ( strrchr(filename, '/') == NULL )
		strncpy(finfo.filename, filename, MAXNAME);
	else
		strncpy(finfo.filename, strrchr(filename, '/')+1, MAXNAME);
	finfo.filename[MAXNAME-1] = 0;
	finfo.id = htons(getpid());
	finfo.modified = stat.st_mtime;
	finfo.fsize = htonl(stat.st_size);
	bfile.header.id = htons(getpid());
	while (1)
	{
		offset = -1;
		bytes = sizeof(finfo);
		memcpy(bfile.buffer, &finfo, bytes);
		do
		{
			bfile.header.offset = htonl(offset);
			bfile.header.size = htons(bytes);
			transmit(sd, &bfile);
			sleep(1);
			if ( offset == -1 )
				offset = 0;
			else
				offset += bytes;
			bytes = read(fd, bfile.buffer, bufsize);
		}
		while ( offset < stat.st_size );
		lseek(fd, 0, SEEK_SET);
	}
	close(fd);
}

/*---------------------------------------------------------------------*/
/*--- main - set up and start the UDP file server.                  ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *args[])
{	int sd, fd;
	int bufsize=0;
	struct in_addr in_addr;
	struct ip_mreq mreq;
	struct sockaddr_in addr;

	if ( count < 4  ||  count > 5 )
	{
		printf(" Usage: %s <addr> <port> <filename> [<bufsize (32768)>]\n", args[0]);
		exit(0);
	}
	if ( count == 5 )
		bufsize = atoi(args[4]);
	if ( bufsize <= 0 )
		bufsize = 32768;
	sd = socket(PF_INET, SOCK_DGRAM, 0);
	if ( inet_aton(args[1], &in_addr) == 0 )
		panic(args[1]);
	if ( ismulticast(in_addr) )
	{
		mreq.imr_multiaddr = in_addr;
		mreq.imr_interface.s_addr = INADDR_ANY;
		if ( setsockopt(sd, SOL_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			panic("Can't add membership");
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(args[2]));
	addr.sin_addr = in_addr;
	if ( connect(sd, (void*)&addr, sizeof(addr)) != 0 )
		panic("Can't connect to address");
	sender(sd, args[3], bufsize);
	close(sd);
}
