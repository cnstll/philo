/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:14:09 by calle             #+#    #+#             */
/*   Updated: 2021/09/09 15:09:19 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philo.h"

void	thinking(t_philo *philo)
{
	int	current_time;
	int	philo_pos;

	philo_pos = philo->pos + 1;
	current_time = get_time_in_ms();
	pthread_mutex_lock(philo->print_lock);
	if (!check_if_philo_died(philo))
		print_philo_status(THINK, current_time - philo->start_time, philo_pos);
	pthread_mutex_unlock(philo->print_lock);
}
