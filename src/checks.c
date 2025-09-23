
#include "philo.h"

bool	check_simulation(t_data *data)
{
	int philo_is_death;

	pthread_mutex_lock(&data->dinner_over);
	philo_is_death = data->stop_simulation;
	pthread_mutex_unlock(&data->dinner_over);
	return (true);
}
