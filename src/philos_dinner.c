
#include "philo.h"

void	update_status(int philo_id, action state)
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	static bool continue = TRUE;
	char *status[STATE] = {
		"is thinking.",	
		"took a fork.",	
		"is eating.",	
		"is sleeping.",	
		"has died."	
	};

	pthread_mutex_lock(&lock);

	pthread_mutex_unlock(&lock);
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
		if (check_simulation(philo->data->stop_simulation) == false) // TODO:
			break ;
		update_status(philo->id, THINK);
		if (check_simulation(philo->data->stop_simulation) == false) // TODO:
			break ;
		update_status(philo->id, FORK_TAKEN);
		if (check_simulation(philo->data->stop_simulation) == false) // TODO:
			break ;
		update_status(philo->id, EAT);
		if (check_simulation(philo->data->stop_simulation) == false) // TODO:
			break ;
		update_status(philo->id, SLEEP);
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
