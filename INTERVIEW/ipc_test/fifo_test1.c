#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define FIFO_SERVER "/home/huang/Desktop/network/fifoserver"


int main(int argc, char **argv)
{
	char r_buf[4096*2];
	int fd;
	int r_size;
	int ret_size;
	
	r_size = atoi(argv[1]);
	printf("request real read bytes %d\n", r_size);
	
	// open 
	memset(r_buf, 0, sizeof(r_buf));
	//fd = open(FIFO_SERVER, O_RDONLY | O_NONBLOCK, 0);
	fd = open(FIFO_SERVER, O_RDONLY, 0);
	if (fd == -1)
	{
		printf("open %s for read error", FIFO_SERVER);
		exit(-1);
	}
	
	while(1)
	{
		memset(r_buf, 0, sizeof(r_buf));
		ret_size = read(fd, r_buf, r_size);
		if (ret_size == -1)
			if (errno == EAGAIN)
				printf("no data availble\n");
		printf("real read bytes %d\n", ret_size);
		sleep(1);
	}
	pause();
	unlink(FIFO_SERVER);
}
