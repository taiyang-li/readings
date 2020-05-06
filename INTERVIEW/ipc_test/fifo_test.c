#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define FIFO_SERVER "/home/huang/Desktop/network/fifoserver"



int main(int argc, char **argv)
{
	int fd;
	char w_buf[4096*2];
	int real_wnum;
	
	memset(w_buf, 0, 4096*2);
	
	// creat
	if (mkfifo(FIFO_SERVER, O_CREAT|O_EXCL) < 0 && (errno != EEXIST))
		printf("cannot create fifoserver\n");
	
	// open
	fd = open (FIFO_SERVER, O_WRONLY , 0);
	//fd = open (FIFO_SERVER, O_WRONLT, 0);
	if (fd == -1 && errno == ENXIO)
		printf("open error: no reading process\n");
	
	// write 2048
	real_wnum = write(fd, w_buf, 2048);
	if (real_wnum == -1)
	{
		if (errno == EAGAIN)
			printf("write to fifo server: try later");
	}
	else
		printf("real write number is %d\n", real_wnum);
	
	// write 5000
	real_wnum = write(fd, w_buf, 5000);
	if (real_wnum == -1)
		if (errno == EAGAIN)
			printf("try later\n");
	else
		printf("real write number is %d\n", real_wnum);

	// write 4096
	real_wnum = write(fd, w_buf, 4096);
	if (real_wnum == -1)
		if (errno == EAGAIN)
			printf("try later\n");
	else
		printf("real write number is %d\n", real_wnum);
}
