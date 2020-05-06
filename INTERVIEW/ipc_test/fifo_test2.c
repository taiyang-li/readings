#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define FIFO_SERVER  "/home/huang/Desktop/network/fifoserver"

int handle_client(char *);


int main()
{
	int r_rd;
	int w_fd;
	pid_t pid;
	if(mkfifo(FIFO_SERVER, O_CREAT | O_EXCL) < 0  && errno != EEXIST)
		printf("cannot create fifoserver\n");
	handle_client(FIFO_SERVER);

}


int handle_client(char *arg)
{
	int ret;
	ret = w_open(arg);
	switch (ret)
	{
		case -1:
		{
			printf("something wrong with open the fifo except for ENXIO\n");  // nosuch device or address
			return -1;
		}
		case 1:
		{
			printf("open server ok\n");
			return 1;
		}
		default:
		{
			printf("w_no_r return ------\n");
			return 0;
		}
	}
	unlink(FIFO_SERVER); 
}



int w_open(char *arg)
{	
	//if(open(arg, O_WRONLY | O_NONBLOCK, 0) == -1)
	if(open(arg, O_WRONLY, 0) == -1)
	{
		if (errno == ENXIO)
			return 0;
		else
			return -1;
	}
	return 1;
}
