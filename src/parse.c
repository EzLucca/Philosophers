
#include "philo.h"

static inline bool	digit_or_spaces(int c, int code)
{
	if (code == DIGITS)
	{
		if (c >= '0' && c <= '9')
			return (true);
		return (false);
	}
	if (code == ISSPACE)
	{
		if ((c >= '\t' && c <= '\r') || c == ' ')
			return (true);
		return (false);
	}
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
	while(digit_or_spaces(nptr[i], ISSPACE) == true)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if(nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] != '\0' && digit_or_spaces(nptr[i], DIGITS))
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

bool	parse_input(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->number_philos = get_number(argv[1]);
	data->time_to_die = get_number(argv[2]) * 1e3;
	data->time_to_eat = get_number(argv[3]) * 1e3;
	data->time_to_sleep = get_number(argv[4]) * 1e3;
	if (argv[5])
		data->cycle = get_number(argv[5]);
	else
		data->cycle = -1;
	data->start_time = get_time();
	data->stop_simulation = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if(!data->forks)
		return (false);
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	if (!data->philo)
		return (false);
	while(i++ < data->number_philos)
		init_philo(&data->philo[i], data, i);
	return (true);
}
