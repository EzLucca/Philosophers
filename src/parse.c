
#include "philo.h"

static inline bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static inline bool ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

static inline int	get_number(const char *nptr)
{
	long long	result;
	size_t		i;

	result = 0;
	i = 0;
	if (!*nptr)
		return (-1);
	while(ft_isspace(nptr[i]) == true)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if(nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result);
}

bool	check_args(char **argv)
{
	int nb;
	int i;

	nb = 0;
	i = 1;
	while (argv[i])
	{
		nb = get_number(argv[i]);
		if (nb <= 0)
			return (false);
		else if (argv[1] && nb < 2)
			return (false);
		i++;
	}
	return (true);
}

void	parse_input(t_data *data, char **argv)
{
	data->n_philos = get_number(argv[1]);
	data->time_to_die = get_number(argv[2]) * 1e3;
	data->time_to_eat = get_number(argv[3]) * 1e3;
	data->time_to_sleep = get_number(argv[4]) * 1e3;
	if (argv[5])
		data->cycle = get_number(argv[5]);
	else
		data->cycle = -1;
}
