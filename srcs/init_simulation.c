#include "../includes/philo.h"

int	init_parameters(char **args, param_t *param)
{
	int	error;

	error = 0;
	param->num_of_philo = ft_lite_atoi(args[1]);
	param->time_to_die = ft_lite_atoi(args[2]);
	param->time_to_eat = ft_lite_atoi(args[3]);
	param->time_to_sleep = ft_lite_atoi(args[4]);
	param->times_must_eat = ft_lite_atoi(args[5]);
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
	if (pthread_mutex_init(&threads->died_lock, NULL) != 0)
		return (1);
	return (0);
}

static void	init_philo_param(
philo_t *philo, threads_data_t *t, param_t *p, int i)
{
		philo->pos = i;
		philo->num_of_philo = p->num_of_philo;
		philo->tt_die = p->time_to_die;
		philo->tt_eat = p->time_to_eat;
		philo->tt_sleep = p->time_to_sleep;
		philo->t_must_eat = p->times_must_eat;
		philo->start_time = p->start_time;
		philo->print_lock = &t->print_lock;
		philo->died_lock = &t->died_lock;
		philo->l_fork = &t->fork[i];
		if (i + 1 == p->num_of_philo)
			philo->r_fork = &t->fork[0];
		else
			philo->r_fork = &t->fork[i + 1];
		philo->someone_died = &t->someone_died;
}

int	init_philo(threads_data_t *threads, param_t *param)
{
	int error;
	int i;

	error = 0;
	i = 0;
	param->start_time = get_time_in_ms();
	while (i < param->num_of_philo && error == 0)
	{
		threads->philos[i] = malloc(sizeof(philo_t));
		init_philo_param(threads->philos[i], threads, param, i);
		if (param->num_of_philo == 1)
		{
			error = pthread_create(
			&threads->philos[i]->id, NULL, life_of_1_philo, threads->philos[i]);
		}
		else 
		{
			error = pthread_create(
			&threads->philos[i]->id, NULL, life_of_philo, threads->philos[i]);
		}
		threads->philos[i]->t_last_ate = get_time_in_ms();
		i++;
	}
	if (error != 0)
		return (1);
	return (0);
}
