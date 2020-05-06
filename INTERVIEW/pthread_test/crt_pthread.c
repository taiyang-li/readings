#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

pthread_t main_tid;

void print_ids(const char *str)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid: %u tid: %u (0x%x)\n", str, (unsigned int)pid, 
			(unsigned int)tid, (unsigned int)tid, (unsigned int)tid);
}

void *func(void *arg)
{
	print_ids("new  thread:");
	return ((void *)0);
}

int main()
{
	int err;
	err = pthread_create(&main_tid, NULL, func, NULL);
	if (err != 0)
	{
		printf("pthread_create");
		return 1;
	}
	printf("main thread: pid: %u tid: %u (0x%x)\n", (unsigned int)getpid(), (unsigned int)pthread_self(), (unsigned int)pthread_self());
	print_ids("main thread");
	sleep(1);
	return 0;
}
