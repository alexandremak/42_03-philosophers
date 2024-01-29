/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:40:33 by amak              #+#    #+#             */
/*   Updated: 2024/01/23 18:55:05 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/* ENUMERATIONS */
typedef enum e_action
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED	
}			t_action;

/* STRUCTURES*/
typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex	mutex;
}			t_fork;

typedef struct s_philo
{
	t_mutex		mutex;
	int			id;
	pthread_t	thread_id;
	int			meals_ate;
	int			full;
	long		time_last_meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	t_mutex		read_mutex;
	t_mutex		write_mutex;
	int			nbr_philos;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	int			nbr_meals;
	long		time_start_dinner;
	int			end_dinner;
	int			all_threads_ready;
	int			nbr_threads_running;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}				t_table;

/* CHECK AND PARSE FUNCTIONS */
int		valid_input(int argc, char **argv);
void	parse_input(t_table *table, char **argv);

/* TABLE INIT FUNCTIONS */
int		init_table(t_table *table);

/* UTILS FUNCTIONS */
long	gettime(void);
void	ft_sleep(long useconds, t_table *table);
void	clean_table(t_table *table);

/* GETTERS AND SETTES FUNCTIONS */
void	set_int(t_mutex *mutex, int *dest, int value);
int		get_int(t_mutex *mutex, int *value);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
void	int_increase(t_mutex *mutex, int *dest);

/* SYNCHRONIZATION FUNCTIONS */
void	wait_all_threads(t_table *table);
int		all_threads_running(t_mutex *mutex, int *threads, int philos_nbr);
int		dinner_ended(t_table *table);

/* WRITE FUNCTION */
void	write_status(t_philo *philo, t_action action);

/* MONITOR FUNTIONS*/
void	*monitor_dinner(void *data);

/* DINNER INIT FUNCTIONS */
void	*routine_alone(void *data);
void	*routine(void *data);
void	init_dinner(t_table *table);

#endif
