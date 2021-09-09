/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:53:33 by calle             #+#    #+#             */
/*   Updated: 2021/09/09 12:53:49 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_philo_status(char *status, int time, int philo_nbr)
{
	ft_putnbr(time);
	ft_putstr(" ");
	ft_putnbr(philo_nbr);
	ft_putstr(status);
}

int	philo_is_full(t_philo *philo)
{
	int		times_must_eat;

	pthread_mutex_lock(philo->must_eat_lock);
	times_must_eat = philo->t_must_eat;
	pthread_mutex_unlock(philo->must_eat_lock);
	if (times_must_eat == 0)
		return (1);
	else
		return (0);
}

int	check_if_philo_died(t_philo *philo)
{
	int	did_someone_die;

	pthread_mutex_lock(philo->died_lock);
	did_someone_die = *philo->someone_died;
	pthread_mutex_unlock(philo->died_lock);
	if (did_someone_die == 1)
		return (1);
	else
		return (0);
}
