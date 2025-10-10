
#include "philo.h"

bool	check_death(t_data *data)
{
	long	philo_is_death;
	int		i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_lock(data->dinner_over) != 0)
			printf("philoisdeath: teste\n");
		philo_is_death = get_time() - data->philo[i].last_meal;
		printf("philoisdeath: %ld\n", philo_is_death);
		if (philo_is_death >= data->time_to_die)
		{
			if (data->stop_simulation == false)
				data->stop_simulation = true;
			check_status(&data->philo[i], DIE);
			pthread_mutex_unlock(data->dinner_over);
			return (true);
		}
		if (data->philo[i].full == true)
		{
			pthread_mutex_unlock(data->dinner_over);
			return (true);
		}
		i++;
	}
	return (false);
}

// static int	someone_is_dead(t_program *program)
// {
// 	int			i;
// 	long long	now;
//
// 	i = 0;
// 	while (i < program->num_philos)
// 	{
// 		pthread_mutex_lock(&program->mtx_meal);
// 		now = get_time();
// 		if (kill_philo(program, i, now))
// 		{
// 			pthread_mutex_unlock(&program->mtx_meal);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&program->mtx_meal);
// 		i++;
// 	}
// 	return (0);
// }

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
