#include "../includes/philo.h"

// 5 args: number_of_philosophers, time_to_die, time_to_eat
// time_to_sleep [number_of_times_each_philosopher_must_eat]

int	init_parameters(char **args, param_t *param)
{
	int	error;

	error = 0;
	param->num_of_philo = ft_lite_atoi(args[1]);
	param->time_to_die = ft_atol(args[2], &error);
	param->time_to_eat = ft_atol(args[3], &error);
	param->time_to_sleep = ft_atol(args[4], &error);
	param->times_must_eat = ft_lite_atoi(args[5]);
	return (0);
}

int	init_threads(threads_t *threads, param_t *param)
{
	int error;
	int i;

	error = 0;
	i = 1;
	threads->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	threads->ret = 0;
	threads->philo = malloc(sizeof(pthread_t) * param->num_of_philo);
	if (!threads->philo)
		return (1);
	while (i <= param->num_of_philo && error == 0)
	{
		error =
		pthread_create(&threads->philo[i], NULL, life_of_philo, &threads->ret);
		i++;
	}
	if (error)
		return (1);
	return (0);
}

int do_philo_simulation(char **args)
{
	param_t		parameters;
	threads_t	threads;

	init_parameters(args, &parameters);
	if (init_threads(&threads, &parameters))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 6 && !arguments_are_valid(argv, argc))
	{
		if (do_philo_simulation(argv))
		{
			printf("ERROR \n");
			return (1);
		}
		printf("OK \n");
		return (0);
	}
	else
	{
		printf("ERROR \n");
		return (1);
	}
	printf("ERROR \n");
	return (1);
}
