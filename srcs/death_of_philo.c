#include "../includes/philo.h"

static int	is_philo_still_alive(philo_t *philo)
{
	int	current_time;

	current_time = get_time_in_ms();
	return (current_time - philo->t_last_ate < philo->tt_die);
}

void	someone_died(threads_data_t *threads)
{
	pthread_mutex_lock(&threads->died_lock);
	threads->someone_died = 1;
	pthread_mutex_unlock(&threads->died_lock);
}

void	death_watch(threads_data_t *d)
{
	int	i;
	philo_t	*philo;

	while (!d->someone_died)
	{
		i = 0;
		while (d->num_of_philos > i)
		{
			philo = d->philos[i];
			if (philo->t_must_eat > 0 && !is_philo_still_alive(philo))
			{
				someone_died(d);
				pthread_mutex_lock(&d->print_lock);
				print_philo_status(
					DEAD, get_time_in_ms() - philo->start_time, philo->pos + 1);
				pthread_mutex_unlock(&d->print_lock);
				break ;
			}
			usleep(100);
			i++;
		}
		while (i - 1 >= 0 && d->philos[i - 1]->t_must_eat == 0)
			i--;
		if (i == 0)
			break;
	}
}
