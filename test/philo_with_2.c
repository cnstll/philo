#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#define NB_OF_PHILOSOPHERS 2
/*
◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

void	prompt_message(char *msg)
{
	int	i;

	i = 0;
	while (msg && msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
}
typedef struct data_s
{
	pthread_mutex_t mutex1;
	pthread_mutex_t mutex2;
}				data_t;

void	init_mutex(pthread_mutex_t	**mutex)
{
	int	i;

	i = 0;
	while (i < NB_OF_PHILOSOPHERS)
	{
		pthread_mutex_init(*(mutex + i * sizeof(pthread_mutex_t)), NULL);
		i++;
	}	
}

void	destroy_mutex(pthread_mutex_t	**mutex)
{
	int	i;

	i = 0;
	while (i < NB_OF_PHILOSOPHERS)
	{
		pthread_mutex_destroy(*(mutex + i * sizeof(pthread_mutex_t)));
		i++;
	}	
}

int *do_stuff(void *data)
{
	data = (pthread_mutex_t *)data;
	pthread_mutex_lock(data->mutex1);
	prompt_message("has taken fork");
	pthread_mutex_lock(&data->mutex2);
	prompt_message("has taken fork");
	prompt_message("is eating");
	pthread_mutex_unlock(data->mutex1);
	pthread_mutex_unlock(data->mutex2);
	prompt_message("is sleeping");
	prompt_message("is thinking");
}

int main(void)
{
	pthread_t	ID[NB_OF_PHILOSOPHERS];
	int			arg;
	int			*ptr1;
	int			*ptr2;
	data_t		data;

	//create a new thread with the ID = 1, the routine print_num and the argument "arg" passed to the routine
	pthread_mutex_init(&data.mutex1, NULL);
	pthread_mutex_init(&data.mutex2, NULL);
	pthread_create(&ID[0], NULL, (void *)&do_stuff, &data);
	pthread_create(&ID[1], NULL, (void *)&do_stuff, &data);
	//the thread of ID = 1 is joined to the parent thread in order to save system resources
	pthread_join(ID[0], (void**)&ptr1);
	pthread_join(ID[1], (void**)&ptr2);
	pthread_mutex_destroy(&data.mutex1);
	pthread_mutex_destroy(&data.mutex2);
	return (0);
}
