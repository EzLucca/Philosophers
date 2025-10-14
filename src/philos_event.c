/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:07:19 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/14 10:38:27 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_event(long time);
static void	release_forks(t_philo *philo);

bool	pick_forks(t_philo *philo, long deadline_time)
{
	if (get_time() < deadline_time)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_TAKEN);
		return (true);
	}
	return (false);
}

bool	eat_or_sleep(t_philo *philo, t_action status)
{
	if (status == EAT)
	{
		philo->last_meal = get_time();
		philo->meals_count += 1;
		if (philo->meals_count == philo->data->rounds_of_meal)
		{
			philo->full = true;
			print_status(philo, EAT);
			time_event(philo->data->time_to_eat);
			release_forks(philo);
			return (false);
		}
		print_status(philo, EAT);
		time_event(philo->data->time_to_eat);
		release_forks(philo);
		return (true);
	}
	if (status == SLEEP)
	{
		print_status(philo, SLEEP);
		time_event(philo->data->time_to_sleep);
		return (true);
	}
	return (false);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	time_event(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}
