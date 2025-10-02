
#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	long	deadline_time;

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
		if(pick_forks(philo, deadline_time) == true)
		{
			eat_or_sleep(philo, EAT);
		}
		if(check_death(philo) == false)
		{
			check_status(philo, DIE);
			break ;
		}
		eat_or_sleep(philo, SLEEP);
	}
	printf("out of loop");
	return (0);
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
		printf("Join thread %d \n", i);
		i++;
	}
	return (true);
}
