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

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

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
	atomic_int			meals_count;
	atomic_long			last_meal;
	bool				full;
	int					id;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread_id;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	atomic_bool			stop_simulation;
	long				number_philos;
	long				rounds_of_meal;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dinner_over;
	t_philo				*philo;
}	t_data;

/* ************************************************************************** */

bool	check_full(t_philo *philo);
bool	check_simulation(t_philo *philo);
bool	eat_or_sleep(t_philo *philo, t_action status);
bool	pick_forks(t_philo *philo, long deadline_time);
bool	prepare_meal(t_data *data);
bool	print_status(t_philo *philo, t_action state);
bool	start_dinner(t_data *data);
bool	validate_args(char **argv);
long	get_time(void);
void	*monitor_routine(t_data *data);
void	*philo_routine(void *arg);
void	destroy_free_mutex(t_data *data, int i);
void	destroy_free_philos(t_data *data);
void	input_msg(int code);
void	parse_input(t_data *data, char **argv);

#endif // !PHILO_H
