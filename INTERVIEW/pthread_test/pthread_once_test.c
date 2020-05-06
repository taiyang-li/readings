#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_once_t once = PTHREAD_ONCE_INIT; //声明变量

// once_run()函数仅执行一次，且究竟在哪个线程中执行是不定的
//尽管pthread_once(&once,once_run)出现在两个线程中
//函数原型：int pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
void once_run(void)
{
	printf("Func: %s in thread: %u\n", 
			__func__, 
			(unsigned int)pthread_self());
}

void *child_1(void *arg)
{
	pthread_t tid;

	tid = pthread_self();
	pthread_once(&once, once_run); //调用once_run
	printf("%s: thread %d returns\n", (char *)arg, (unsigned int)tid);

	return NULL;
}

void *child_2(void *arg)
{
	pthread_t tid;

	tid = pthread_self();
	pthread_once(&once, once_run); //调用once_run
	printf("%s: thread %d returns\n", (char *)arg, (unsigned int)tid);

	return NULL;
}

//******* main *******//
int main(void)
{
	pthread_t tid1, tid2;

	printf("hello main\n");
	pthread_create(&tid1, NULL, child_1, (void *)"child_1");
	pthread_create(&tid2, NULL, child_2, (void *)"child_2");

	pthread_join(tid1, NULL);  //main主线程等待线程tid1返回
	pthread_join(tid2, NULL);  //main主线程等待线程tid2返回
	printf("bye main\n");

	return 0;
}

