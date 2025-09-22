
#include "philo.h"

void	error_exit(char *error)
{
	printf("%s\n", error);
}

void	destroy_free_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			input_msg(3);
		}
		i++;
		free(data->forks);
	}
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
