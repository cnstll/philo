#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	struct	timeval current_time;
	long	start;
	long	now;


	gettimeofday(&current_time, NULL);
	start = current_time.tv_usec;
	usleep(1000);
	gettimeofday(&current_time, NULL);
	now = current_time.tv_usec;
	printf("time elapsed ms : %ld\n",
    (now - start)/1000);

  return 0;
}
