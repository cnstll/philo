#include "../includes/philo.h"

static void	destroy_philos(threads_data_t *threads, param_t *param)
{
	int i;

	i = 0;
	while (i < param->num_of_philo)
	{
		pthread_join(threads->philos[i]->id, NULL);
		i++;
	}
}

static void	free_philos(threads_data_t *threads, param_t *param)
{
	int i;

	i = 0;
	while (i < param->num_of_philo)
	{
		free(threads->philos[i]);
		i++;
	}
}

static void	destroy_mutexes(threads_data_t *threads, param_t *param)
{
	int i;

	i = 0;
	while (i < param->num_of_philo)
	{
		pthread_mutex_destroy(&threads->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&threads->print_lock);
	pthread_mutex_destroy(&threads->died_lock);
}

void	threads_cleaning_wrapper(threads_data_t *threads, param_t *param)
{
	destroy_philos(threads, param);
	free_philos(threads, param);
	destroy_mutexes(threads, param);
	free(threads->philos);
	free(threads->fork);
}
