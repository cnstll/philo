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
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
		print_philo_status(" is thinking\n", current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
}

void	sleeping(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
		print_philo_status(" is sleeping\n", current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
	ms_sleep(philo->tt_sleep);
}

void	eating(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	if (*philo->someone_died == 0)
		print_philo_status(" is eating\n", current_time - philo->start_time, philo_pos);
	philo->t_must_eat--;
	philo->t_last_ate = current_time;
	pthread_mutex_unlock(philo->print_lock);
	ms_sleep(philo->tt_eat);
}

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
		print_philo_status(" has taken a fork\n", current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
}

void	put_fork_down(philo_t *philo, char fork_side)
{
	if (fork_side == 'r')
		pthread_mutex_unlock(philo->r_fork);
	else
		pthread_mutex_unlock(philo->l_fork);
}

void	*life_of_philo(void *thread_infos)
{
	philo_t	*philo;
	
	philo = (philo_t *)(thread_infos);
	if (philo->pos % 2)
		usleep(15000);
	while (philo->t_must_eat > 0 && philo->alive && *philo->someone_died == 0)
	{
		get_fork(philo, RIGHT_FORK);
		get_fork(philo, LEFT_FORK);
		eating(philo);
		put_fork_down(philo, LEFT_FORK);
		put_fork_down(philo, RIGHT_FORK);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
