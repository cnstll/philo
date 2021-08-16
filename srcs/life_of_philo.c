#include  "../includes/philo.h"

void *life_of_philo(void *data)
{
	philo_t	*philos;
	
	philos = (philo_t *)(data);
	while (1)
	{
		pthread_mutex_lock(&philos->fork[*philos->pos - 1]);
		printf("timestamp_in_ms %d  has taken a fork\n", *philos->pos);
		pthread_mutex_unlock(&philos->fork[*philos->pos - 1]);
		usleep(100);
		free(philos->pos);
	}
	return (0);
}
