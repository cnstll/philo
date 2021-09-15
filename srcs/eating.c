/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:16:42 by calle             #+#    #+#             */
/*   Updated: 2021/09/15 11:20:01 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_fork(t_philo *philo, char fork_side)
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
	if (!check_if_philo_died(philo))
	{
		print_philo_status(
			TAKE_FORK, current_time - philo->start_time, philo_pos);
	}
	pthread_mutex_unlock(philo->print_lock);
}

void	put_fork_down(t_philo *philo, char fork_side)
{
	if (fork_side == 'r')
		pthread_mutex_unlock(philo->r_fork);
	else
		pthread_mutex_unlock(philo->l_fork);
}

static void	pick_forks(t_philo *philo)
{
	get_fork(philo, RIGHT_FORK);
	get_fork(philo, LEFT_FORK);
}

void	eating(t_philo *philo)
{
	int	current_time;
	int	philo_pos;

	philo_pos = philo->pos + 1;
	pick_forks(philo);
	current_time = get_time_in_ms();
	pthread_mutex_lock(philo->print_lock);
	if (!check_if_philo_died(philo))
		print_philo_status(EAT, current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->ate_lock);
	philo->t_last_ate = current_time;
	pthread_mutex_unlock(philo->ate_lock);
	pthread_mutex_lock(philo->must_eat_lock);
	philo->t_must_eat--;
	pthread_mutex_unlock(philo->must_eat_lock);
	ms_sleep(philo->tt_eat);
	put_fork_down(philo, LEFT_FORK);
	put_fork_down(philo, RIGHT_FORK);
}
