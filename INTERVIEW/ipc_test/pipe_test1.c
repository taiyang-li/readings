#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	int pipe_fd[2];
	pid_t pid;
	char r_buf[100];
	char *w_buf;
	int write_num;
	int cmd;
	

	memset(r_buf, 0, sizeof(r_buf));


	// create a pipe
	if (pipe(pipe_fd) < 0)
	{
		printf("pipe create error\n");
		return -1;
	}

	// child  process
	if ((pid = fork()) == 0 )
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		sleep(10);
		exit(0);
	}
	else if (pid > 0)
	{
		sleep(1);
		close(pipe_fd[0]);
		strcpy(w_buf, "111");
		if ((write_num = write(pipe_fd[1], w_buf, 4)) == -1)
			printf("write to pipe error\n");
		else
			printf("the bytes write to pipe is %d\n",write_num );
		close(pipe_fd[1]);
	}
}
