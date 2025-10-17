/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:00:42 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/13 19:01:09 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	creation_of_pthreads(t_data *data, int i);

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	if (creation_of_pthreads(data, i) == false)
		return (false);
	while (i < data->number_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	return (true);
}

static bool	creation_of_pthreads(t_data *data, int i)
{
	int	count;

	count = 0;
	while (i < data->number_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, philo_routine
				, &data->philo[i]) != 0)
		{
			while (i > count)
			{
				data->stop_simulation = true;
				if (pthread_join(data->philo[count].thread_id, NULL) != 0)
					return (false);
				count++;
			}
			input_msg(4);
			return (false);
		}
		i++;
	}
	data->start = true;
	monitor_routine(data);
	return (true);
}
