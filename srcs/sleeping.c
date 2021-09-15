/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:17:30 by calle             #+#    #+#             */
/*   Updated: 2021/09/15 11:19:52 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	int	current_time;
	int	philo_pos;

	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	pthread_mutex_lock(philo->print_lock);
	if (!check_if_philo_died(philo))
		print_philo_status(SLEEP, current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
	ms_sleep(philo->tt_sleep);
}
