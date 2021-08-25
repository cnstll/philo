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

void	init_philo_param(philo_t *philo, threads_data_t *t, param_t *p, int i)
{
		philo->pos = i;
		philo->alive = 1;
		philo->num_of_philo = p->num_of_philo; 
		philo->tt_die = p->time_to_die;
		philo->t_last_ate = get_time_in_ms();
		philo->tt_eat = p->time_to_eat;
		philo->tt_sleep = p->time_to_sleep;
		philo->t_must_eat = p->times_must_eat;
		philo->start_time = p->start_time;
		philo->print_lock = &t->print_lock;
		philo->l_fork = &t->fork[i];
		if (i + 1 == p->num_of_philo)
			philo->r_fork = &t->fork[0];
		else
			philo->r_fork = &t->fork[i + 1];
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
		init_philo_param(threads->philos[i], threads, param, i);
		error = pthread_create(
		&threads->philos[i]->id, NULL, life_of_philo, threads->philos[i]);
		init_death_watch(threads->philos[i], &threads->philos[i]->death_watch_id);
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
