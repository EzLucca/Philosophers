/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:03:05 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/13 19:05:19 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_assingment(t_data *data, int i);
static bool	init_philos(t_data *data);
static bool	init_forks(t_data *data);
static bool	init_mutexes(t_data *data);

bool	prepare_meal(t_data *data)
{
	if (init_mutexes(data) == false)
		return (false);
	if (init_forks(data) == false)
		return (false);
	if (init_philos(data) == false)
		return (false);
	return (true);
}

static bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->dinner_over, NULL) != 0)
	{
		input_msg(3);
		return (false);
	}
	return (true);
}

static bool	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (!data->forks)
	{
		input_msg(2);
		return (false);
	}
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_free_mutex(data, i);
			input_msg(3);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	if (!data->philo)
	{
		destroy_free_mutex(data, i);
		input_msg(2);
		return (false);
	}
	while (i < data->number_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_count = 0;
		data->philo[i].full = false;
		data->philo[i].last_meal = data->start_time;
		fork_assingment(data, i);
		data->philo[i].data = data;
		i++;
	}
	return (true);
}

static void	fork_assingment(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->number_philos];
	}
	else
	{
		data->philo[i].l_fork = &data->forks[(i + 1) % data->number_philos];
		data->philo[i].r_fork = &data->forks[i];
	}
}
