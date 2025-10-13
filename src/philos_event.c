/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:07:19 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/13 19:08:15 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_event(t_philo *philo, long time);

bool	pick_forks(t_philo *philo, long deadline_time)
{
	if (get_time() < deadline_time)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, FORK_TAKEN);
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, FORK_TAKEN);
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, FORK_TAKEN);
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, FORK_TAKEN);
		}
		return (true);
	}
	return (false);
}

bool	eat_or_sleep(t_philo *philo, action status)
{
	if (status == EAT)
	{
		philo->last_meal = get_time();
		philo->meals_count += 1;
		if (philo->meals_count == philo->data->rounds_of_meal)
			philo->full = true;
		print_status(philo, EAT);
		time_event(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (true);
	}
	if (status == SLEEP)
	{
		print_status(philo, SLEEP);
		time_event(philo, philo->data->time_to_sleep);
		return (true);
	}
	return (false);
}

static void	time_event(t_philo *philo, long time)
{
	long	start;

	(void)philo;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}
