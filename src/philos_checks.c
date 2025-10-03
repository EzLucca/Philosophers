
#include "philo.h"

bool	check_death(t_philo *philo)
{
	long	philo_is_death;

	if (philo->full == true)
		return (false);
	philo_is_death = get_time() - philo->last_meal;
	// printf("time: %ld\n", get_time());
	// printf("time to die: %ld\n", philo->data->time_to_die);
	// printf("last_meal: %ld\n", philo->last_meal);
	// printf("philo_death: %ld\n", philo_is_death);
	if (philo_is_death >= philo->data->time_to_die)
	{
		// printf("test");
		pthread_mutex_lock(philo->data->dinner_over);
		philo->data->stop_simulation = true;
		pthread_mutex_unlock(philo->data->dinner_over);
		return (false);
	}
	return (true);
}

bool	check_status(t_philo *philo, action state)
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	char *status[STATE] = {
		"is thinking.",	
		"took a fork.",	
		"is eating.",	
		"is sleeping.",	
		"has died."	
	};

	pthread_mutex_lock(&lock);
	printf("%ld, philo %d %s\n", get_time() - philo->data->start_time, philo->id, status[state]);
	pthread_mutex_unlock(&lock);
	return (true);
}
