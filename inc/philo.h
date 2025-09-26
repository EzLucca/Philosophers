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

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DIGITS 0
# define ISSPACE 1

typedef struct s_data t_data;
typedef struct s_philo t_philo;

enum action
{
	THINK,
	EAT,
	SLEEP,
	DIE,
};

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
	long				number_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				cycle;
	long				start_time;
	bool				stop_simulation;
	pthread_mutex_t		dinner_over; //protect access of stop_simulation
	pthread_mutex_t		*forks;
	t_philo				*philo;
} t_data;

/* ************************************************************************** */
// parce.c
void	parse_input(t_data *data, char **argv);
bool	check_args(char **argv);

// init.c
bool	prepare_meal(t_data *data);

// utils .c
void	input_msg(int code);
long	get_time(void);
void	destroy_free_mutex(t_data *data, int i);

// dinner.c
bool	start_dinner(t_data *data);

// checks.c
bool	check_simulation(t_data *data);

//TESTING:
void print_data(t_data *data);
#endif // !PHILO_H
