
#include "philo.h"

void	destroy_free_mutex(t_data *data, int i)
{
	while (i > 0)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			input_msg(3);
		i--;
	}
	free(data->forks);
	data->forks = NULL;
	if (pthread_mutex_destroy(data->dinner_over) != 0)
		input_msg(3);
	free(data->dinner_over);
	data->dinner_over = NULL;
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
