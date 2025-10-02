
#include "philo.h"

bool	pick_forks(t_philo *philo, long	deadline_time)
{
	if (get_time() < deadline_time)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->r_fork);
			check_status(philo, FORK_TAKEN);
			pthread_mutex_lock(&philo->l_fork);
			check_status(philo, FORK_TAKEN);
		}
		else
		{
			pthread_mutex_lock(&philo->l_fork);
			check_status(philo, FORK_TAKEN);
			pthread_mutex_lock(&philo->r_fork);
			check_status(philo, FORK_TAKEN);
		}
		return (true);
	}
	return (false);
}

void	time_event(t_philo *philo, long time)
{
	long	start;

	start = get_time();
	// printf("start: %ld\n", start);
	while ((get_time() - start) < time)
	{
		// printf("start: %ld\n", start);
		if (check_death(philo))
			break ;
		usleep(500);
	}
}

void	eat_or_sleep(t_philo *philo, action status)
{
	if (status == EAT)
	{
		philo->last_meal = get_time();
		philo->meals_count += 1;

		if (philo->meals_count == philo->data->rounds_of_meal)
			philo->full = true;
		check_status(philo, EAT);
		time_event(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	if (status == SLEEP)
	{
		check_status(philo, SLEEP);
		time_event(philo, philo->data->time_to_sleep);
	}
}

// 	long	start;
//
// 	start = get_time();
// 	while ((get_time() - start) < philo->data->time_to_eat)
// 	{
// 		if (check_end_flag(data))
// 			break ;
// 		usleep(500);
// 	}
