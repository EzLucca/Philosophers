
#include "philo.h"

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->meals_count = 0;
	philo->full = false;
	philo->last_meal = data->start_time;
	philo->l_fork = data->forks[i];
	philo->r_fork = data->forks[i];
}
