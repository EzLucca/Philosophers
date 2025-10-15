/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:56:38 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/14 11:14:06 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	satisfaction_philo(t_data *data, int i);
static bool	check_death(t_data *data);

void	*monitor_routine(t_data *data)
{
	while (1)
	{
		if (check_death(data) == true)
		{
			return (NULL);
		}
	}
	return (0);
}

static bool	check_death(t_data *data)
{
	long	philo_is_death;
	int		i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_mutex_lock(&data->dinner_over);
		philo_is_death = get_time() - data->philo[i].last_meal;
		if (philo_is_death >= data->time_to_die)
		{
			print_status(&data->philo[i], DIE);
			if (data->stop_simulation == false)
			{
				data->stop_simulation = true;
			}
			pthread_mutex_unlock(&data->dinner_over);
			return (true);
		}
		if (satisfaction_philo(data, i) == true)
			return (true);
		pthread_mutex_unlock(&data->dinner_over);
		i++;
	}
	return (false);
}

static bool	satisfaction_philo(t_data *data, int i)
{
	static int				full = 0;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	if (check_full(&data->philo[i]) == true)
	{
		pthread_mutex_lock(&lock);
		full++;
		if (full == data->number_philos)
		{
			pthread_mutex_unlock(&data->dinner_over);
			pthread_mutex_unlock(&lock);
			return (true);
		}
		pthread_mutex_unlock(&lock);
	}
	return (false);
}

bool	print_status(t_philo *philo, t_action state)
{
	static bool				should_print = true;
	long					deadline_time;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	static char				*status[STATE] = {
		"is thinking",	
		"has taken a fork",	
		"is eating",	
		"is sleeping",	
		"died"	
	};

	deadline_time = get_time() + philo->data->time_to_die;
	pthread_mutex_lock(&lock);
	if (philo->data->stop_simulation == true)
		should_print = false;
	if (should_print == true && get_time() < deadline_time)
		printf("%ld %d %s\n", get_time() - philo->data->start_time,
			philo->id, status[state]);
	pthread_mutex_unlock(&lock);
	return (true);
}

bool	check_full(t_philo *philo)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (philo->meals_count == philo->data->rounds_of_meal)
	{
		philo->full = true;
		pthread_mutex_unlock(&lock);
		return (true);
	}
	pthread_mutex_unlock(&lock);
	return (false);
}
