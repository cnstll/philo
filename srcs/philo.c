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
	printf("num of philo %d \n", param->num_of_philo);
	if (param->num_of_philo == 0)
		return (1);
	return (0);
}

int	init_mutexes(philo_t *threads, param_t *param)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	threads->fork = malloc(sizeof(pthread_mutex_t) * param->num_of_philo);
	while (i < param->num_of_philo && error == 0)
	{
		error = pthread_mutex_init(&threads->fork[i], NULL);
		i++;
	}
	if (error != 0)
		return (1);
	if (pthread_mutex_init(&threads->lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_philo(philo_t *data, param_t *param)
{
	int error;
	int i;

	data->philo = malloc(sizeof(philo_t) * param->num_of_philo);
	if (!data->philo)
		return (1);
	error = 0;
	i = 1;
	data->pos = malloc(sizeof(int) * param->num_of_philo);
	while (i <= param->num_of_philo && error == 0)
	{
		data->pos = i;
		error = pthread_create(&data->philo[i - 1], NULL, life_of_philo, data);
		i = i + 2;
	}
	i = 2;
	usleep(100);
	while (i <= param->num_of_philo && error == 0)
	{
		data->pos = malloc(sizeof(int));
		*data->pos = i;
		error = pthread_create(&data->philo[i - 1], NULL, life_of_philo, data);
		i = i + 2;
	}
	free(data->pos);
	if (error != 0)
		return (1);
	return (0);
}

int do_philo_simulation(char **args)
{
	param_t		parameters;
	philo_t		data;

	init_parameters(args, &parameters);
	if (init_mutexes(&data, &parameters))
		return (1);
	if (init_philo(&data, &parameters))
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
