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
	print_philo_status(" is thinking\n", current_time - philo->start_time, philo_pos);
	usleep(1000);
	pthread_mutex_unlock(philo->print_lock);
}

void	sleeping(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	print_philo_status(" is sleeping\n", current_time - philo->start_time, philo_pos);
	usleep(philo->tt_sleep);
	pthread_mutex_unlock(philo->print_lock);
}

void	eating(philo_t *philo)
{
	int	current_time;
	int	philo_pos;

	pthread_mutex_lock(philo->print_lock);
	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	print_philo_status(" is eating\n", current_time - philo->start_time, philo_pos);
	usleep(philo->tt_eat);
	philo->t_must_eat--;
	philo->t_last_ate = current_time;
	pthread_mutex_unlock(philo->print_lock);
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
	while (1 && philo->t_must_eat > 0 && philo->alive)
	{
		thinking(philo);
		if (philo->pos + 1 == philo->num_of_philo)
		{
			get_fork(philo, RIGHT_FORK);
			get_fork(philo, LEFT_FORK);
			eating(philo);
			put_fork_down(philo, LEFT_FORK);
			put_fork_down(philo, RIGHT_FORK);
		}
		else
		{
			get_fork(philo, LEFT_FORK);
			get_fork(philo, RIGHT_FORK);
			eating(philo);
			put_fork_down(philo, RIGHT_FORK);
			put_fork_down(philo, LEFT_FORK);
		}
		sleeping(philo);
	}
	return (0);
}
