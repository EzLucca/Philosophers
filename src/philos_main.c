/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:05:36 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/13 19:05:37 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	input_msg(int code)
{
	if (code == 1)
	{
		printf("Invalid argument.\n");
		printf("Correct usage: ./philo [1] [2] [3] [4] [5]\n");
		printf("./philo: the executable.\n");
		printf("[1]: Number of philosophers (>2).\n");
		printf("[2]: Time in ms to die (+).\n");
		printf("[3]: Time in ms to eat (+).\n");
		printf("[4]: Time in ms to sleep (+).\n");
		printf("Optional argument:\n");
		printf("[5]: Times that each philosopher eat on the simulation (+).\n");
	}
	if (code == 2)
		printf("Malloc fail.\n");
	if (code == 3)
		printf("Mutex fail.\n");
	if (code == 4)
		printf("Pthread creation fail.\n");
}

int	main(int argc, char **argv)
{
	t_data		data;

	if ((argc == 5 || argc == 6) && validate_args(argv))
	{
		parse_input(&data, argv);
		if (prepare_meal(&data) == false)
			return (3);
		start_dinner(&data);
		destroy_free_mutex(&data, data.number_philos);
		destroy_free_philos(&data);
		return (0);
	}
	input_msg(1);
	return (1);
}
