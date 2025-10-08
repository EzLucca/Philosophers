
#include "philo.h"

bool	single_philo(t_philo *philo)
{
	if (philo->data->number_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		check_status(philo, FORK_TAKEN);
		usleep(philo->data->time_to_die * 1000);
		check_status(philo, DIE);
		pthread_mutex_unlock(philo->l_fork);
		return (true);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	return (false);
}

bool	actions(t_philo *philo, long deadline_time)
{
	check_status(philo, THINK);
	if(pick_forks(philo, deadline_time) == false)
		return (false);
	if(eat_or_sleep(philo, EAT) == false)
		return (false);
	if(eat_or_sleep(philo, SLEEP) == false)
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_philo *philo;
	long	deadline_time;
	static bool no_death;

	no_death = true;
	philo = (t_philo *)arg;
	if (single_philo(philo) == false)
	{
		while (no_death)
		{
			deadline_time = get_time() + philo->data->time_to_die;
			printf("time:%ld deadline: %ld\n", get_time() - philo->data->start_time, deadline_time);
			if (actions(philo, deadline_time) == false)
			{
				if (philo->full != true && no_death == true)
					no_death = false;
				break ;
			}
			usleep(1000);
		}
	}
	return (0);
}

bool	check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dinner_over);
	if (philo->data->stop_simulation == true)
	{
		pthread_mutex_unlock(philo->data->dinner_over);
		return (true);
	}
	pthread_mutex_unlock(philo->data->dinner_over);
	return (false);
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, routine, &data->philo[i]) != 0)
		{
			while (i--)
				pthread_join(data->philo[i].thread_id, NULL);
			input_msg(4);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < data->number_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	return (true);
}
