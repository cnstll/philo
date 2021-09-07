/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:13:38 by calle             #+#    #+#             */
/*   Updated: 2021/09/07 18:13:58 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	do_philo_simulation(char **args)
{
	t_param			param;
	t_threads_data	threads;

	init_parameters(args, &param);
	threads.someone_died = 0;
	threads.num_of_philos = param.num_of_philo;
	threads.fork = malloc(sizeof(pthread_mutex_t) * param.num_of_philo);
	if (!threads.fork)
		return (1);
	threads.philos = malloc(sizeof(t_philo *) * param.num_of_philo);
	if (!threads.philos)
	{
		free(threads.fork);
		return (1);
	}
	if ((init_mutexes(&threads, &param)) || (init_philo(&threads, &param)))
		return (1);
	death_watch(&threads);
	threads_cleaning_wrapper(&threads, &param);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 6 && !arguments_are_valid(argv, argc))
	{
		if (do_philo_simulation(argv))
		{
			ft_putstr(SIM_ERROR);
			return (1);
		}
		return (0);
	}
	else
	{
		ft_putstr(ARG_ERROR);
		return (1);
	}
}
