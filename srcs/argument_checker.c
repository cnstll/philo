#include "../includes/philo.h"

int	arguments_are_valid(char **args, int nb_args)
{
	int	i;
	int	j;
	int	err;

	i = 0;
	while (++i < nb_args)
	{
		err = 0;
		j = 0;
		if ((i == 1 || i == 5) && !is_within_int_range(ft_atol(args[i], &err)))
			return (1);
		else
			ft_atol(args[i], &err);
		if (err != 0)
			return (1);
		while (args[i][j])
			if (!is_digit(args[i][j++]))
				return (1);
	}
	return (0);
}
