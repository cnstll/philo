#include  "../includes/philo.h"

void	print_philo_status(char *status, int time, int philo_nbr)
{
	ft_putnbr(time);
	ft_putstr(" ");
	ft_putnbr(philo_nbr);
	ft_putstr(status);
}

void	thinking(philo_t *philo)
{
	int	current_time;

	pthread_mutex_lock(philo->print_lock);
	current_time = get_time_in_ms();
	//print_philo_status("  is thinking\n", current_time - philo->start_time, philo->pos);
	printf("%d %d is thinking\n", current_time - philo->start_time, philo->pos);
	usleep(200);
	pthread_mutex_unlock(philo->print_lock);
}

void *life_of_philo(void *thread_infos)
{
	philo_t	*philo;
	
	philo = (philo_t *)(thread_infos);
	while (1 && philo->t_must_eat > 0)
	{
		thinking(philo);
		usleep(100000);
	}
	return (0);
}
