/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_of_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:11:25 by calle             #+#    #+#             */
/*   Updated: 2021/09/07 18:13:19 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_philo_still_alive(t_philo *philo)
{
	int	current_time;
	int	diff_time;

	current_time = get_time_in_ms();
	pthread_mutex_lock(philo->ate_lock);
	diff_time = current_time - philo->t_last_ate;
	pthread_mutex_unlock(philo->ate_lock);
	return (diff_time < philo->tt_die);
}

void	someone_died(t_threads_data *threads)
{
	pthread_mutex_lock(&threads->died_lock);
	threads->someone_died = 1;
	pthread_mutex_unlock(&threads->died_lock);
}

void	print_death(t_threads_data *threads, t_philo *philo)
{
	pthread_mutex_lock(&threads->print_lock);
	print_philo_status(
		DEAD, get_time_in_ms() - philo->start_time, philo->pos + 1);
	pthread_mutex_unlock(&threads->print_lock);
}

void	death_watch(t_threads_data *d)
{
	int		i;

	i = 1;
	while (!d->someone_died && i >= 0)
	{
		i = 0;
		while (d->num_of_philos > i)
		{
			if (!philo_is_full(d->philos[i])
				&& !is_philo_still_alive(d->philos[i]))
			{
				someone_died(d);
				print_death(d, d->philos[i]);
				break ;
			}
			usleep(100);
			i++;
		}
		while (--i >= 0)
			if (!philo_is_full(d->philos[i]))
				break ;
	}
}
