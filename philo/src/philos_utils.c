/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:05:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/14 10:29:42 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_free_mutex(t_data *data, int i)
{
	int	count;

	count = 0;
	while (i > count)
	{
		if (pthread_mutex_destroy(&data->forks[count]) != 0)
			input_msg(3);
		count++;
	}
	free(data->forks);
	data->forks = NULL;
	if (pthread_mutex_destroy(&data->dinner_over) != 0)
		input_msg(3);
}

void	destroy_free_philos(t_data *data)
{
	free(data->philo);
	data->philo = NULL;
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
