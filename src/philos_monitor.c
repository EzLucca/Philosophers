
#include "philo.h"

// void	*monitor_routine(void *arg)
void	*monitor_routine(t_data *data)
{
	// t_data *data;
	//
	// data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) == true)
			return (NULL);
	}
	return (0);
}

bool	check_death(t_data *data)
{
	long	philo_is_death;
	int		i;

	i = 0;
	while (i < data->number_philos)
	{
		// pthread_mutex_lock(data->dinner_over);
		philo_is_death = get_time() - data->philo[i].last_meal;
		if (philo_is_death >= data->time_to_die)
		{
			if (data->stop_simulation == false)
				data->stop_simulation = true;
			print_status(&data->philo[i], DIE);
			// printf("died\n");
			// pthread_mutex_unlock(data->dinner_over);
			// printf("unlocked\n");
			return (true);
		}
		if (data->philo[i].full == true)
		{
			// pthread_mutex_unlock(data->dinner_over);
			return (true);
		}
		// pthread_mutex_unlock(data->dinner_over);
		i++;
	}
	return (false);
}

bool	print_status(t_philo *philo, action state)
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	static bool should_print = true;
	char *status[STATE] = {
		"is thinking",	
		"has taken a fork",	
		"is eating",	
		"is sleeping",	
		"died"	
	};
	long	deadline_time;

	deadline_time = get_time() + philo->data->time_to_die;
	pthread_mutex_lock(&lock);
	if (should_print && get_time() < deadline_time)
		printf("%ld %d %s\n", get_time() - philo->data->start_time,
				philo->id, status[state]);
	if (philo->data->stop_simulation)
		should_print = false;
	pthread_mutex_unlock(&lock);
	return (true);
}
