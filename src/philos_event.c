
#include "philo.h"

static void	time_event(t_philo *philo, long time);

bool	pick_forks(t_philo *philo, long	deadline_time)
{
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	// while (check_death(philo) == false && get_time() < deadline_time)
	while (get_time() < deadline_time)
	{
		pthread_mutex_lock(&lock);
		if (philo->data->using_forks == false)
		{
			if (philo->id % 2 == 0)
			{
				pthread_mutex_lock(philo->r_fork);
				check_status(philo, FORK_TAKEN);
				pthread_mutex_lock(philo->l_fork);
				check_status(philo, FORK_TAKEN);
				// philo->data->using_forks = true;
			}
			else
			{
				pthread_mutex_lock(philo->l_fork);
				check_status(philo, FORK_TAKEN);
				pthread_mutex_lock(philo->r_fork);
				check_status(philo, FORK_TAKEN);
				// philo->data->using_forks = true;
			}
			pthread_mutex_unlock(&lock);
			return (true);
		}
		pthread_mutex_unlock(&lock);
		usleep(250);
	}
	check_death(philo);
	return (false);
}

bool	eat_or_sleep(t_philo *philo, action status)
{
	if (check_death(philo) == false)
	{
		if (status == EAT)
		{
			philo->last_meal = get_time();
			philo->meals_count += 1;
			if (philo->meals_count == philo->data->rounds_of_meal)
				philo->full = true;
			check_status(philo, EAT);
			time_event(philo, philo->data->time_to_eat);
			philo->data->using_forks = false;
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (true);
		}
		if (status == SLEEP)
		{
			check_status(philo, SLEEP);
			time_event(philo, philo->data->time_to_sleep);
			return (true);
		}
		// philo->data->using_forks = false;
	}
	return (false);
}

static void	time_event(t_philo *philo, long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (check_death(philo) == true)
			break ;
		usleep(500);
	}
}
