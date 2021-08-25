#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *string)
{
	int	i;

	i = 0;
	while (string && string[i])
	{
		ft_putchar(string[i]);
		i++;
	}
}

void	ft_putnbr(int	nbr)
{
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
}

int		get_time_in_ms(void)
{
	struct	timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int main()
{
	int		start_time;

	start_time = get_time_in_ms();
	while (1)
	{
		ft_putnbr(get_time_in_ms() - start_time);
		ft_putstr("\n");
		usleep(1000000);
	}
	return (0);
}
