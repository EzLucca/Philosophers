
#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	int	deadline_time;

	philo = (t_philo *)arg;
	deadline_time = get_time() + philo->data->time_to_die;
	while (true)
	{
		pthread_mutex_lock(philo->data->dinner_over);
		if (philo->data->stop_simulation == true) // TODO:
		{
			pthread_mutex_unlock(philo->data->dinner_over);
			break ;
		}
		pthread_mutex_unlock(philo->data->dinner_over);
		check_status(philo, THINK);
		pick_forks(philo, deadline_time);
		check_status(philo, FORK_TAKEN);
		check_status(philo, FORK_TAKEN);
		if(check_death(philo) == false)
			check_status(philo, DIE);
		check_status(philo, EAT);
		check_status(philo, SLEEP);
	}
	return (0);
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, routine, data) != 0)
		{
			while (i--)
				pthread_join(data->philo[i].thread_id, NULL);
			input_msg(4);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i++ < data->number_philos)
		pthread_join(data->philo[i].thread_id, NULL);
	return (true);
}
