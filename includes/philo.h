#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# define SIM_ERROR "ERROR: error encountered during simulation" 
# define ARG_ERROR "ERROR: invalid arguments"  
# define LEFT_FORK 'l'
# define RIGHT_FORK 'r'
# define THINK " is thinking\n" 
# define EAT " is eating\n" 
# define SLEEP " is sleeping\n" 
# define TAKE_FORK " has taken a fork\n" 
# define DEAD " died\n" 

/*
** ------------------ ARGS HOLDING STRUCT ------------------
*/
typedef struct param_s
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_must_eat;
	int		start_time;
}				param_t;

/*
** ------------------ INDVIDUAL PHILO STRUCT ------------------
*/
typedef struct philo_s
{
	int				pos;
	int				alive;
	int				t_last_ate;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				t_must_eat;
	int				start_time;
	int				num_of_philo;
	pthread_t		id;
	pthread_t		death_watch_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*died_lock;
	pthread_mutex_t	*ate_lock;
	int				*someone_died;
}				philo_t;

/*
** ------------------ GENERAL THREADS DATA STRUCT ------------------
*/
typedef struct threads_data_s
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	died_lock;
	pthread_mutex_t	ate_lock;
	pthread_mutex_t	*fork;
	philo_t			**philos;
	int				someone_died;
	int				num_of_philos;
}				threads_data_t;

/*
** ------------------ ARGUMENT CHECKER ------------------
*/
int			arguments_are_valid(char **args, int nb_args);

/*
** ------------------ THREADS ROUTINE ------------------
*/
void		*life_of_philo(void *data);
void		*life_of_1_philo(void *data);
/*
** ------------------ INIT MUTEX, THREADS AND MEM ------------------
*/
int			init_mutexes(threads_data_t *threads, param_t *param);
int			init_parameters(char **args, param_t *param);
int			init_philo(threads_data_t *threads, param_t *param);
/*
** ------------------ PHILO ACTIONS ------------------
*/
void		death_watch(threads_data_t *d);;
void		thinking(philo_t *philo);
void		sleeping(philo_t *philo);
void		get_fork(philo_t *philo, char fork_side);
void		put_fork_down(philo_t *philo, char fork_side);
void		eating(philo_t *philo);
void		someone_died(threads_data_t *threads);
/*
** ------------------ HELPER FUNCTIONS ------------------
*/
long long	ft_atol(char *str, int *error);
int			ft_lite_atoi(char *s);
int			is_digit(char character);
int			is_within_int_range(long long number);
void		ft_putstr(char *string);
void		ft_putnbr(int nbr);
int			get_time_in_ms(void);
void		ms_sleep(int sleep_time);
void		print_philo_status(char *status, int time, int philo_nbr);	
/*
** ------------------ EXIT FUNC ------------------
*/
void		threads_cleaning_wrapper(threads_data_t *threads, param_t *param);
#endif
