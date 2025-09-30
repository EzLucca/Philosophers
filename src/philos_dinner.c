
#include "philo.h"

void	update_status(t_philo philo, action state)
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
	printf("%-4ld, philo %d %s\n.", get_time() - philo->data->start_time, philo->id, status[state]);
	pthread_mutex_unlock(&lock);
}

void	*routine(void *arg)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = (t_philo *)arg;
	while (philo->data->stop_simulation == false && i <= philo->data->cycle)
	{
		// if (check_simulation(philo->data->stop_simulation) == false) // TODO:
		// 	break ;
		update_status(philo, THINK);
		update_status(philo, FORK_TAKEN);
		update_status(philo, FORK_TAKEN);
		if(check_death(philo) == false)
			update_status(philo, DIE);
		update_status(philo, EAT);
		update_status(philo, SLEEP);
		i++;
	}
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
				pthread_join(&data->philo[i].thread_id, NULL);
			input_msg(4);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i++ < data->number_philos)
		pthread_join(&data->philo[i].thread_id, NULL);
	return (true);
}
