
#include "philo.h"

bool	check_death(t_philo *philo)
{
	long	philo_is_death;


	philo_is_death = get_time() - philo->last_meal;
	if (philo_is_death >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dinner_over);
		philo->data->stop_simulation == true;
		pthread_mutex_unlock(&philo->data->dinner_over);
	}
	return (true);
}
