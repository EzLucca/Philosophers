
#include "philo.h"

bool	check_simulation(t_data *data)
{
	int philo_is_death;

	pthread_mutex_lock(&data->dinner_over);
	philo_is_death = data->stop_simulation;
	pthread_mutex_unlock(&data->dinner_over);
	return (true);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_simulation(philo->data) == false) // TODO:
			break ;
		//think;
		//pick_forks();
		//eat_meal();
		//drop_forks();
		//deep_sleep();
	}
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, routine, data) != 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
