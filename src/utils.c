
#include "philo.h"

void	error_exit(char *error)
{
	printf("%s\n", error);
}

void	clean_kitchen(t_data *data)
{
	int i;

	i = 0;
	if (data->forks)
		free(data->forks);
	while (i < data->number_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			input_msg(3);
		}
		i++;
	}
	// while (i < data->number_philos)
	// {
	// 	free(data->forks);
	// 	i++;
	// }
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
