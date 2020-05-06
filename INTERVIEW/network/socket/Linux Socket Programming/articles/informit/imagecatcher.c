/* imagecatcher.c
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
/*** imagecatcher.c                                                        ***/
/***                                                                       ***/
/*** The client for receiving multicast files over UDP                     ***/
/*****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <resolv.h>
#include "imagecaster.h"

#define max(a,b)	((a)>(b)?(a):(b))
#define min(a,b)	((a)>(b)?(b):(a))

#define MAXTABLE		5
#define MAXFRAGS		20

#define WENT_OKAY		0
#define BAD_CHECKSUM	-1
#define BAD_HASH		-2
#define BAD_SEEK		-3

static int cnt=0;
static struct filerec
{
	u32 ipaddr;
	u16 pid;
	int ffd;
	u32 fsize;
	char filename[MAXNAME];
	char ftemp[MAXNAME];
	struct fragstruct
	{
		u32 head;
		u32 tail;
	} frags[MAXFRAGS];
} ftable[MAXTABLE];

/*---------------------------------------------------------------------*/
/*--- addfrag - track the received data range (overlapping allowed).---*/
/*---------------------------------------------------------------------*/
int addfrag(struct filerec* filerec, u32 offset, u32 size)
{	int i, added=0;
	struct fragstruct* frags = filerec->frags;
	struct fragstruct new={offset, offset+size};

	for ( i = 0; i < MAXFRAGS  &&  frags[i].tail != 0; i++ )
		if ( (frags[i].head <= new.head  &&  new.head <= frags[i].tail)  ||
			 (new.head <= frags[i].head  &&  frags[i].head <= new.tail) )
		{	int j;
			u32 tail=max(new.tail, frags[i].tail);

			for ( j = i+1; j < MAXFRAGS  &&  frags[j].head <= new.tail  &&  frags[j].tail != 0; j++ )
				tail = max(frags[j].tail, tail);
			new.head = min(new.head, frags[i].head);
			new.tail = max(new.tail, tail);
			frags[i] = new;
			while ( j < MAXFRAGS  &&  frags[j].tail != 0 )
				frags[++i] = frags[j++];
			while ( ++i < MAXFRAGS  &&  frags[i].tail != 0 )
				frags[i].tail = 0;
			added = 1;
			break;
		}
		else if ( new.tail < frags[i].head )
		{	struct fragstruct temp;
			int j=i;
			do
			{
				temp = frags[j];
				frags[j] = new;
				new = temp;
			}
			while ( j < MAXFRAGS-1  &&  frags[j++].tail != 0 );
			added = 1;
			break;
		}
	if ( !added )
		frags[i] = new;
#ifdef DEBUG
	printf("Adding: Head=%d Tail=%d (offset=%d, size=%d)\n", new.head, new.tail, offset, size);
	for ( i = 0; i < MAXFRAGS  &&  frags[i].tail != 0; i++ )
		printf("#%d: head=%03d tail=%03d [%d]\n", i+1, frags[i].head, frags[i].tail, filerec->fsize);
	printf("------\n");
#endif
	return (filerec->fsize == (frags[0].tail - frags[0].head));
}

/*---------------------------------------------------------------------*/
/*--- getfd - find or allocate destination files.                   ---*/
/*---------------------------------------------------------------------*/
#define TEMPFILE	"image.XXXXXX"
#define INDXFILE	"index.XXXXXX"

int getfd(u32 addr_in, u16 pid)
{	int i;

	for ( i = 0; i < MAXTABLE; i++ )
		if ( ftable[i].ipaddr == addr_in  &&  ftable[i].pid == pid )
			return i;
	for ( i = 0; i < MAXTABLE; i++ )
		if ( ftable[i].ipaddr == 0 )
			break;
	if ( i < MAXTABLE )
	{
		ftable[i].ipaddr = addr_in;
		ftable[i].pid = pid;
		strcpy(ftable[i].ftemp, TEMPFILE);
		ftable[i].ffd = mkstemp(ftable[i].ftemp);
		if ( ftable[i].ffd >= 0 )
			return i;
		else
			return -1;
	}
	return -1;
}

/*---------------------------------------------------------------------*/
/*--- storerec - put data fragment in file and register range.      ---*/
/*---------------------------------------------------------------------*/
int storerec(struct sockaddr_in *addr, struct bfile *bfile)
{	int index;
	u32 offset = ntohl(bfile->header.offset);
	u16 size = ntohs(bfile->header.size);

	index = getfd(ntohl(addr->sin_addr.s_addr), ntohs(bfile->header.id));
	if ( index < 0 )
		fprintf(stderr, "Can't find or add new file stream\n");
	else if ( lseek(ftable[index].ffd, offset, SEEK_SET) >= 0 )
	{
		write(ftable[index].ffd, bfile->buffer, size);
		if ( addfrag(&ftable[index], offset, size) )
		{
			close(ftable[index].ffd);
			rename(ftable[index].ftemp, ftable[index].filename);
			printf("File %s complete!\n", ftable[index].filename);
			memset(&ftable[index], 0, sizeof(ftable[index]));
		}
	}
	else
		return BAD_SEEK;
	return WENT_OKAY;
}

/*---------------------------------------------------------------------*/
/*--- validwrite - check packet; if header set data. Otherwise, put ---*/
/*--- data to file                                                  ---*/
/*---------------------------------------------------------------------*/
int validwrite(struct sockaddr_in *addr, struct bfile* bfile)
{	u16 sum;
	u32 hash;

	sum = ntohs(bfile->header.checksum);
	bfile->header.checksum = 0;
	if ( checksum(bfile, sizeof(bfile->header)+ntohs(bfile->header.size)) != sum )
		return BAD_CHECKSUM;
	hash = ntohl(bfile->header.hash);
	bfile->header.hash == 0;
	if ( dx_hack_hash(bfile->buffer, ntohs(bfile->header.size)) != hash )
		return BAD_HASH;
	if ( bfile->header.offset == -1 )
	{	struct bfile_info *finfo = (void*)bfile->buffer;
		int index;
printf("file=%s size=%d date=%s", finfo->filename, ntohl(finfo->fsize), ctime(&finfo->modified));
		index = getfd(ntohl(addr->sin_addr.s_addr), ntohs(bfile->header.id));
		ftable[index].fsize = ntohl(finfo->fsize);
		strncpy(ftable[index].filename, finfo->filename, MAXNAME);
		ftable[index].filename[MAXNAME-1] = 0;
	}
	else
		return storerec(addr, bfile);
	return WENT_OKAY;
}

/*---------------------------------------------------------------------*/
/*--- receiver - catch each message.                                ---*/
/*---------------------------------------------------------------------*/
void receiver(int sd)
{	int fd=-1;
	int offset=0, bytes;
	struct stat stat;
	struct bfile bfile;
	struct sockaddr_in addr;

	do
	{	int len=sizeof(addr);
		u32 hash;
		u16 sum;

		bytes = recvfrom(sd, (void*)&bfile, sizeof(bfile), 0, (void*)&addr, &len);
#ifdef DEBUG
		printf("Received offset=%d size=%d from %s:%d\n", ntohl(bfile.header.offset),
		ntohs(bfile.header.size), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
#endif
		switch ( validwrite(&addr, &bfile) )
		{
			case BAD_SEEK: perror("Could not seek"); break;
			case BAD_CHECKSUM: fprintf(stderr, "Failed checksum\n"); break;
			case BAD_HASH: fprintf(stderr, "Failed hash check\n"); break;
		}
	}
	while ( 1 );
}

/*---------------------------------------------------------------------*/
/*--- main - set up socket and run.                                 ---*/
/*---------------------------------------------------------------------*/
int main(int count, char *args[])
{	int sd, fd;
	const int on=1;
	struct in_addr in_addr;
	struct ip_mreq mreq;
	struct sockaddr_in addr;

	if ( count != 3 )
	{
		printf(" Usage: %s <addr> <port>\n", args[0]);
		exit(0);
	}
	sd = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(args[2]));
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sd, (void*)&addr, sizeof(addr)) != 0 )
		panic("Can't bind to port");
	if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != 0 )
		panic("Can't enable port sharing");
	if ( inet_aton(args[1], &in_addr) == 0 )
		panic(args[1]);
	if ( ismulticast(in_addr) )
	{
		mreq.imr_multiaddr = in_addr;
		mreq.imr_interface.s_addr = INADDR_ANY;
		if ( setsockopt(sd, SOL_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			panic("Can't add membership");
	}
	receiver(sd);
	close(sd);
}
