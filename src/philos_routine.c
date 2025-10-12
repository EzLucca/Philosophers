
#include "philo.h"

static bool	single_philo(t_philo *philo);
// static bool	actions(t_philo *philo, long deadline_time);

void	*philo_routine(void *arg)
{
	t_philo *philo;
	long	deadline_time;
	static bool no_death;

	no_death = true;
	philo = (t_philo *)arg;
	if (single_philo(philo) == false)
	{
		while (philo->data->stop_simulation != true)
		{
			deadline_time = get_time() + philo->data->time_to_die;

			print_status(philo, THINK);
			if(pick_forks(philo, deadline_time) == false)
				return (false);
			if(eat_or_sleep(philo, EAT) == false)
				return (false);
			if(eat_or_sleep(philo, SLEEP) == false)
				return (false);

			// if (actions(philo, deadline_time) == false)
			// {
			if (philo->full != true && no_death == true)
			{
				no_death = false;
				break ;
			}
			// }
			usleep(1000);
		}
	}
	return (0);
}

static bool	single_philo(t_philo *philo)
{
	if (philo->data->number_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_TAKEN);
		usleep(philo->data->time_to_die * 1000);
		print_status(philo, DIE);
		pthread_mutex_unlock(philo->l_fork);
		return (true);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	return (false);
}

// static bool	actions(t_philo *philo, long deadline_time)
// {
// 	print_status(philo, THINK);
// 	if(pick_forks(philo, deadline_time) == false)
// 		return (false);
// 	if(eat_or_sleep(philo, EAT) == false)
// 		return (false);
// 	if(eat_or_sleep(philo, SLEEP) == false)
// 		return (false);
// 	return (true);
// }
