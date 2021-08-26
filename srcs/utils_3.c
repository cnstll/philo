#include "../includes/philo.h"

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
