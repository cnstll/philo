#include "../includes/philo.h"

int do_philo_simulation(char **args)
{
	param_t			param;
	threads_data_t	threads;

	init_parameters(args, &param);
	threads.someone_died = 0;
	threads.num_of_philos = param.num_of_philo;
	threads.fork = malloc(sizeof(pthread_mutex_t) * param.num_of_philo);
	if (!threads.fork)
		return (1);
	threads.philos = malloc(sizeof(philo_t *) * param.num_of_philo);
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

int main(int argc, char **argv)
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
