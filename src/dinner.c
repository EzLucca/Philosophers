
#include "philo.h"

void	update_status(int philo_id, action state)
{
}

void	check_simulation(t_data data)
{
	if (data->stop_simulation == true)
		return (false);
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
		update_status(philo->id, THINK);
		update_status(philo->id, EAT);
		update_status(philo->id, SLEEP);
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
	//pthread_join();
	return (true);
}
