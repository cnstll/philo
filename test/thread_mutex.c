#include <pthread.h>
#include <stdio.h>
#include <limits.h>

//need a global var as function var are destroyed with the fonction end call
int ret = 0;

int *print_num(void *num)
{
	printf("Number to print in the thread: %d\n", * (int *)num);
	//pthread_exit(&ret);
	return (&ret);
}

int main(void)
{
	pthread_t ID;
	int	arg;
	int	*ptr;
	int max_thread;

	arg = 1;
	max_thread = PTHREAD_THREADS_MAX;
	//create a new thread with the ID = 1, the routine print_num and the argument "arg" passed to the routine
	pthread_create(&ID, NULL, (void *)&print_num, &arg);
	//the thread of ID = 1 is joined to the parent thread in order to save system resources
	pthread_join(ID, (void**)&ptr);
	printf("Return of thread %d is %d\n", arg, *ptr);
	printf("Max num of thread %d\n", max_thread);
	return (0);
}
