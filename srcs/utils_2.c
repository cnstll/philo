#include "../includes/philo.h"

int		ft_lite_atoi(char *s)
{
	char	*nbr;
	int		n;
	int		i;

	nbr = (char *)s;
	i = 0;
	n = 0;
	while (nbr[i] > 47 && nbr[i] < 58)
	{
		if (nbr[i + 1] > 47 && nbr[i + 1] < 58)
			n = (n + (int)(nbr[i]) % 48) * 10;
		else
			n = (n + (int)(nbr[i]) % 48);
		i++;
	}
	return (n);
}
