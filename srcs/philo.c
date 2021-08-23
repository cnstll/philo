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
	param->start_time = get_time_in_ms();
	if (param->num_of_philo == 0)
		return (1);
	return (0);
}

int	init_mutexes(threads_data_t *threads, param_t *param)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < param->num_of_philo && error == 0)
	{
		error = pthread_mutex_init(&threads->fork[i], NULL);
		i++;
	}
	if (error != 0)
		return (1);
	if (pthread_mutex_init(&threads->print_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_philo(threads_data_t *threads, param_t *param)
{
	int error;
	int i;

	error = 0;
	i = 0;
	while (i < param->num_of_philo && error == 0)
	{
		threads->philos[i] = malloc(sizeof(philo_t));
		threads->philos[i]->pos = i;
		threads->philos[i]->tt_die = param->time_to_die;
		threads->philos[i]->tt_eat = param->time_to_eat;
		threads->philos[i]->tt_sleep = param->time_to_sleep;
		threads->philos[i]->t_must_eat = param->times_must_eat;
		threads->philos[i]->start_time = param->start_time;
		threads->philos[i]->print_lock = &threads->print_lock;
		threads->philos[i]->l_fork = &threads->fork[i];
		if (i + 1 == param->num_of_philo)
			threads->philos[i]->r_fork = &threads->fork[0];
		else
			threads->philos[i]->r_fork = &threads->fork[i + 1];
		error = pthread_create(&threads->philos[i]->id, NULL, life_of_philo, threads->philos[i]);
		i++;
	}
	if (error != 0)
		return (1);
	return (0);
}

void	destroy_philos(threads_data_t *threads, param_t *param)
{
	int i;

	i = 0;
	while (i < param->num_of_philo)
	{
		pthread_join(threads->philos[i]->id, NULL);
		i++;
	}
}

int do_philo_simulation(char **args)
{
	param_t			param;
	threads_data_t	threads;

	init_parameters(args, &param);
	threads.fork = malloc(sizeof(pthread_mutex_t) * param.num_of_philo);
	if (!threads.fork)
		return (1);
	if (init_mutexes(&threads, &param))
		return (1);
	threads.philos = malloc(sizeof(philo_t *) * param.num_of_philo);
	if (!threads.philos)
	{
		//loop to destroy fork mutexes
		free(threads.fork);
		return (1);
	}
	if (init_philo(&threads, &param))
		return (1);
	destroy_philos(&threads, &param);
	//free forks and philos
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
