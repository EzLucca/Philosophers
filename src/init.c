
#include "philo.h"

static void	fork_assingment(t_data *data, int i);
static void	init_philos(t_data *data);
static bool	init_mutexes_orders(t_data *data);
static bool	init_data(t_data *data);

bool	prepare_meal(t_data *data)
{
	if (init_data(data) == false)
		return (false);
	if (init_mutexes_orders(data) == false)
		return (false);
	init_philos(data);
	return (true);
}

static void	fork_assingment(t_data *data, int i)
{
	if ((i + 1) % 2 == 0)
	{
		data->philo[i].l_fork = data->forks[i];
		data->philo[i].r_fork = data->forks[(i + 1) % data->number_philos];
	}
	else
	{
		data->philo[i].l_fork = data->forks[(i + 1) % data->number_philos];
		data->philo[i].r_fork = data->forks[i];
	}
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_count = 0;
		data->philo[i].full = false;
		data->philo[i].last_meal = data->start_time;
		fork_assingment(data, i);
		i++;
	}
}

static bool	init_mutexes_orders(t_data *data)
{
	int i;

	i = 0;
	while(i < data->number_philos)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != 0) //0 on success
		{
			destroy_free_mutex(data, i);
			input_msg(3);
			return (false);
		}
		i++;
	}
	if(pthread_mutex_init(&data->dinner_over, NULL) != 0) //0 on success
	{
		destroy_free_mutex(data, i);
		input_msg(3);
		return (false);
	}
	return (true);
}

static bool	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if(!data->forks)
	{
		input_msg(2);
		return (false);
	}
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	if (!data->philo)
	{
		free(data->forks);
		input_msg(2);
		return (false);
	}
	return (true);
}
