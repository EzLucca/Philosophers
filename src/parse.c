
#include "philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static bool ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

static int	get_number(const char *nptr)
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

bool	parse_input(t_data *data, char **argv)
{
	data->n_philos = get_number(argv[1]);
	if (data->n_philos == -1)
		return (false);
	data->time_to_die = get_number(argv[2]) * 1e3;
	if (data->time_to_die == -1)
		return (false);
	data->time_to_eat = get_number(argv[3]) * 1e3;
	if (data->time_to_eat == -1)
		return (false);
	data->time_to_sleep = get_number(argv[4]) * 1e3;
	if (data->time_to_sleep == -1)
		return (false);
	if (argv[5])
		data->cycle = get_number(argv[5]);
	else
		data->cycle = -1;
	return (true);
}
