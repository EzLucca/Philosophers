
#include "philo.h"

static bool	creation_of_pthreads(t_data *data, int i);
static bool	creation_of_monitor(t_data *data, int i);

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	if (creation_of_pthreads(data, i) == false)
		return (false);
	if (creation_of_monitor(data, i) == false)
		return (false);
	while (i < data->number_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	return (true);
}

static bool	creation_of_pthreads(t_data *data, int i)
{
	while (i < data->number_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, philo_routine, &data->philo[i]) != 0)
		{
			while (i--)
				pthread_join(data->philo[i].thread_id, NULL);
			input_msg(4);
			return (false);
		}
		printf("create %d\n", i);
		i++;
	}
	return (true);
}

static bool	creation_of_monitor(t_data *data, int i)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, &data) != 0)
	{
		while (i < data->number_philos)
		{
			pthread_join(data->philo[i].thread_id, NULL);
			i++;
		}
		input_msg(4);
		return (false);
	}
	return (true);
}
