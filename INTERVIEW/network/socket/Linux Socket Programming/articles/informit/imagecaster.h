#include <sys/types.h>
#include <resolv.h>

void panic(char *msg);
#define panic(msg)	{ perror(msg); exit(-1); }
#define MAXNAME		20
#define MAXPACKET	65535

typedef unsigned int u32;
typedef signed int i32;
typedef unsigned short u16;
typedef signed short i16;

struct bfile_info
{
	u16 id;
	char filename[MAXNAME];
	time_t modified;
	u32 fsize;
};

struct bfile_header
{
	u16 id;
	u16 size;
	u32 offset;
	u16 checksum;
	u32 hash;
};

struct bfile
{
	struct bfile_header header;
	unsigned char buffer[MAXPACKET-sizeof(struct bfile_header)];
};

u32 dx_hack_hash(const void *d, int len);
u16 checksum(const void *d, int len);
int ismulticast(struct in_addr in_addr);
