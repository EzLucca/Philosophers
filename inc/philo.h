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
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define DIGITS 0
# define ISSPACE 1

typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef struct s_philo
{
	int					id;
	int					meals_count;
	bool				full;
	long				last_meal;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		r_fork;
	pthread_t			thread_id;
	t_data				*data;
} t_philo;

typedef struct s_data
{
	int					number_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					cycle;
	long				start_time;
	int					stop_simulation;
	pthread_mutex_t		*forks;
	t_philo				*philo;
} t_data;

/* ************************************************************************** */
// parce.c
bool	parse_input(t_data *data, char **argv);
bool	check_args(char **argv);

// init.c
// void	init_data(t_data *data);
void	init_philo(t_philo *philo, t_data *data, int i);

// utils .c
// void	error(char *error);
void	input_msg(int code);
long	get_time(void);

#endif // !PHILO_H
