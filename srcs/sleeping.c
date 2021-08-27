#include  "../includes/philo.h"

void	sleeping(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
		print_philo_status(SLEEP, current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
	ms_sleep(philo->tt_sleep);
}
