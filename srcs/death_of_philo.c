#include "../includes/philo.h"

int	init_death_watch(philo_t *philo, pthread_t *death_watch_id)
{
	int			error;

	error = 0;
	error = pthread_create(death_watch_id, NULL, death_watch, philo);
	if (error != 0)
		return (1);
	return (0);
}

int	is_philo_still_alive(philo_t *philo)
{
	int	current_time;

	current_time = get_time_in_ms();
	return (current_time - philo->t_last_ate < philo->tt_die);
}

void	*death_watch(void *philo_data)
{
	philo_t	*philo;

	philo = (philo_t *)(philo_data);
	while (philo->alive)
		if (!is_philo_still_alive(philo))
			philo->alive = 0;
	pthread_mutex_lock(philo->print_lock);
	print_philo_status(" died\n", get_time_in_ms() - philo->start_time, philo->pos + 1);
	pthread_mutex_unlock(philo->print_lock);
	return (0);
}
