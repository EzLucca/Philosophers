/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:59:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/16 14:23:45 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	int			id;
	int			meals;
	bool		full;
	int			last_meal;
	t_mtx		l_fork;
	t_mtx		r_fork;
	pthread_t	thread_id;
} t_philo;

typedef struct s_data
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		cycle;
	long	start_time;
	t_philo	*philo;
} t_data;

// parce.c
bool	parse_input(t_data *data, char **argv);

// utils .c
void	error_exit(char *error);

#endif // !PHILO_H
