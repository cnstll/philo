#include  "../includes/philo.h"

void	*life_of_1_philo(void *thread_infos)
{
	philo_t	*philo;
	
	philo = (philo_t *)(thread_infos);
	get_fork(philo, LEFT_FORK);
	put_fork_down(philo, LEFT_FORK);
	while (*philo->someone_died == 0)
		;
	return (0);
}

void	*life_of_philo(void *thread_infos)
{
	philo_t	*philo;
	
	philo = (philo_t *)(thread_infos);
	if (philo->pos % 2)
		usleep(15000);
	while (philo->t_must_eat > 0 && *philo->someone_died == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
