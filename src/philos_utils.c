/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:05:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/13 19:07:07 by edlucca          ###   ########.fr       */
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
	if (pthread_mutex_destroy(data->dinner_over) != 0)
		input_msg(3);
	free(data->dinner_over);
	data->dinner_over = NULL;
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

void	print_philo(t_philo *philo)
{
	printf("data->philo[%d].id: %d\n", philo->id, philo->id);
	printf("data->philo[%d].meals_count: %d\n", philo->id, philo->meals_count);
	printf("data->philo[%d].full: %d\n", philo->id, philo->full);
	printf("data->philo[%d].last_meal %ld\n", philo->id, philo->last_meal);
}

void	print_data(t_data *data)
{
	printf("data->number_philos %ld\n", data->number_philos);
	printf("data->time_to_die: %ld\n", data->time_to_die);
	printf("data->time_to_eat: %ld\n", data->time_to_eat);
	printf("data->time_to_sleep: %ld\n", data->time_to_sleep);
	printf("data->rounds_of_meal: %ld\n", data->rounds_of_meal);
	printf("data->start_time: %ld\n", data->start_time);
	printf("data->stop_simulation: %d\n", data->stop_simulation);
}
