/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:59:31 by edlucca           #+#    #+#             */
/*   Updated: 2025/10/14 11:11:25 by edlucca          ###   ########.fr       */
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
# include <stdatomic.h>

# define DIGITS 0
# define ISSPACE 1

typedef struct	s_data t_data;
typedef struct	s_philo t_philo;

typedef enum action
{
	THINK,
	FORK_TAKEN,
	EAT,
	SLEEP,
	DIE,
	STATE,
}	t_action;

typedef struct s_philo
{
	int					id;
	atomic_int			meals_count;
	bool				full;
	atomic_long			last_meal;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread_id;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	long				number_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	atomic_long			rounds_of_meal;
	long				start_time;
	atomic_bool			stop_simulation;
	pthread_mutex_t		*dinner_over; //protect access of stop_simulation
	pthread_mutex_t		*forks;
	t_philo				*philo;
}	t_data;

/* ************************************************************************** */
// philo_dinner.c
bool	start_dinner(t_data *data);

// philo_event.c
bool	pick_forks(t_philo *philo, long deadline_time);
bool	eat_or_sleep(t_philo *philo, t_action status);

// philo_init.c
bool	prepare_meal(t_data *data);

// philo_main.c
void	input_msg(int code);

// philo_monitor.c
void	*monitor_routine(t_data *data);
bool	print_status(t_philo *philo, t_action state);
bool	check_full(t_philo *philo);

// philo_parse.c
void	parse_input(t_data *data, char **argv);
bool	validate_args(char **argv);

// philo_routine.c
void	*philo_routine(void *arg);

// utils .c
long	get_time(void);
void	destroy_free_mutex(t_data *data, int i);
void	destroy_free_philos(t_data *data);

//TESTING:
void	print_data(t_data *data);
void	print_philo(t_philo *philo);
#endif // !PHILO_H
