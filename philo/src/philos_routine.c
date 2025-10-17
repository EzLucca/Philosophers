/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:02:04 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/14 11:14:59 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	single_philo(t_philo *philo);
static void	set_starting(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo				*philo;
	long				deadline_time;

	philo = (t_philo *)arg;
	set_starting(philo);
	if (single_philo(philo) == false)
	{
		while (1)
		{
			deadline_time = get_time() + philo->data->time_to_die;
			print_status(philo, THINK);
			if (pick_forks(philo, deadline_time) == false)
				return (0);
			if (eat_or_sleep(philo, EAT) == false)
				return (0);
			if (check_full(philo) == true)
				return (0);
			if (eat_or_sleep(philo, SLEEP) == false)
				return (0);
			if (check_simulation(philo) == true)
				return (0);
			usleep(1000);
		}
	}
	return (0);
}

static void	set_starting(t_philo *philo)
{
	static pthread_mutex_t	start_line = PTHREAD_MUTEX_INITIALIZER;
	bool					start;
	bool					stop;

	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&start_line);
		start = philo->data->start;
		stop = philo->data->stop_simulation;
		pthread_mutex_unlock(&start_line);
		if (start || stop)
			break ;
	}
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

bool	check_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dinner_over);
	if (philo->data->stop_simulation == true)
	{
		pthread_mutex_unlock(&philo->data->dinner_over);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dinner_over);
	return (false);
}
