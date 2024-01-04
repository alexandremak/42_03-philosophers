/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 02:42:54 by amak              #+#    #+#             */
/*   Updated: 2024/01/04 20:57:36 by amak             ###   ########.fr       */
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
# include <errno.h>

/* ENUMERATION */

typedef enum e_option
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_option;

typedef enum e_time_code
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}			t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

/* STRUCTURES */

typedef pthread_mutex_t t_mutex;
typedef struct s_table 	t_table;

typedef struct s_fork
{
	int		id;
	t_mutex	mutex;
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	long 		nr_meals;
	int			full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mutex		mutex;
	t_table		*table;
} 				t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		nbr_meals;
	long		start_simulation;
	int			end_simulation;
	int			all_threads_ready;
	long		nbr_threads_running;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}				t_table;

/* MAIN FUNCTIONS*/


/* UTILS FUNCTIONS */
void	error_exit(const char *error_msg);
long	gettime(t_time_code time_code);
void	ft_sleep(long usec, t_table *table);
void	clean(t_table *table);

/* PARSING FUNCTIONS */
void 	parse_input(t_table *table, char **argv);

/* SAFE FUNCTIONS */
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mutex *mutex, t_option option);
void	safe_thread_handle(pthread_t *thread, void *(foo)(void *), void *data,
		t_option option);

/* SYNCHRO UTILS */
void	wait_all_threads(t_table *table);
int		all_threads_running(t_mutex *mutex, long *threads, long philo_nbr);
void	increase_unit(t_mutex *mutex, long *value);

/* GETTERS AND SETTERS FUNCTIONS*/
void	set_bool(t_mutex *mutex, int *dest, int value);
int		get_bool(t_mutex *mutex, int *value);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
int		simulation_finished(t_table *table);

/* INIT FUNCTIONS */
void 	table_init(t_table *table);

/* WRITE FUNCTIONS */
void	write_status(t_philo_status status, t_philo *philo);

/* PRINT TABLE FUNCTIONS */
void	print_table(t_table *table);

/* MONITOR FUNCTIONS */
void	*monitor_dinner(void *data);

/* SIMULATIONS FUNCTIONS */
void	dinner_start(t_table *table);

#endif
