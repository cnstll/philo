#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
#include <stdio.h>

typedef struct param_s
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_must_eat;
}				param_t;

typedef struct philo_s
{
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	pthread_t		*philo;
	int				*pos;
}				philo_t;

int			arguments_are_valid(char **args, int nb_args);
long long	ft_atol(char *str, int *error);
int			ft_lite_atoi(char *s);
int			is_digit(char character);
int			is_within_int_range(long long number);
void		*life_of_philo(void *data);

#endif
