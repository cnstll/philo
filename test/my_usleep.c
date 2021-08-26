#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int		get_time_in_ms(void)
{
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ms_sleep(int sleep_time)
{
	int	tic;
	int	time_elapsed; 
	int	start_time;

	tic = 100;
	time_elapsed = 0;
	start_time = get_time_in_ms();
	while (sleep_time > time_elapsed)
	{
		time_elapsed = get_time_in_ms() - start_time;
		usleep(tic);
	}
}

int	main()
{
	int	current_time;
	int	start_time;

	start_time = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		printf("TIME: %d\n", current_time - start_time); 
		ms_sleep(100);
	}
}
