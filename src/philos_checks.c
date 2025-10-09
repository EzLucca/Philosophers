
#include "philo.h"

bool	check_death(t_philo *philo)
{
	long	philo_is_death;

	philo_is_death = get_time() - philo->last_meal;

	// printf("time: %ld\nstart_time: %ld\nlast_meal: %ld\ntime_die: %ld\n", get_time(), philo->data->start_time, philo->last_meal, philo->data->time_to_die);
	// printf("philo_is_death: %ld\ntime_die: %ld\n",
			// philo_is_death,
			// philo->data->time_to_die);

	if (philo_is_death >= philo->data->time_to_die)
	{
		pthread_mutex_lock(philo->data->dinner_over);
		if (philo->data->stop_simulation == false)
			philo->data->stop_simulation = true;
		check_status(philo, DIE);
		pthread_mutex_unlock(philo->data->dinner_over);
		return (true);
	}
	if (philo->full == true)
		return (true);
	return (false);
}

bool	check_status(t_philo *philo, action state)
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
