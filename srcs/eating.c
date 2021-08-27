#include  "../includes/philo.h"

void	get_fork(philo_t *philo, char fork_side)
{
	int	current_time;
	int	philo_pos;

	if (fork_side == 'r')
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
	{
		print_philo_status(
				TAKE_FORK ,current_time - philo->start_time, philo_pos);
	}
	pthread_mutex_unlock(philo->print_lock);
}

void	put_fork_down(philo_t *philo, char fork_side)
{
	if (fork_side == 'r')
		pthread_mutex_unlock(philo->r_fork);
	else
		pthread_mutex_unlock(philo->l_fork);
}



void	eating(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	if (philo->pos + 1 == philo->num_of_philo)
	{
		get_fork(philo, LEFT_FORK);
		get_fork(philo, RIGHT_FORK);
	}
	else
	{
		get_fork(philo, RIGHT_FORK);
		get_fork(philo, LEFT_FORK);
	}
	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
		print_philo_status(EAT, current_time - philo->start_time, philo_pos);
	philo->t_last_ate = current_time;
	pthread_mutex_unlock(philo->print_lock);
	philo->t_must_eat--;
	ms_sleep(philo->tt_eat);
	put_fork_down(philo, LEFT_FORK);
	put_fork_down(philo, RIGHT_FORK);
}
