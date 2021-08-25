#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
#include <stdio.h>
# define LEFT_FORK 'l'
# define RIGHT_FORK 'r'

typedef struct param_s
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_must_eat;
	int		start_time;
}				param_t;

typedef struct philo_s
{
	int				pos;
	int				alive;
	long			t_last_ate;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	int				t_must_eat;
	int				start_time;
	int				num_of_philo;
	pthread_t		id;
	pthread_t		death_watch_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
}				philo_t;

typedef struct threads_data_s
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork;
	philo_t			**philos;
}				threads_data_t;

int			arguments_are_valid(char **args, int nb_args);
long long	ft_atol(char *str, int *error);
int			ft_lite_atoi(char *s);
int			is_digit(char character);
int			is_within_int_range(long long number);
void		*life_of_philo(void *data);
void		ft_putstr(char *string);
void		ft_putnbr(int nbr);
int			get_time_in_ms(void);
void		*death_watch(void *threads_info);
int			init_death_watch(philo_t *threads, pthread_t *death_watch_id);
void		print_philo_status(char *status, int time, int philo_nbr);	
#endif
