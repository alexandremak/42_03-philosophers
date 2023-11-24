/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 02:42:54 by amak              #+#    #+#             */
/*   Updated: 2023/11/24 22:18:50 by amak             ###   ########.fr       */
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
	long 		meals;
	int			full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;
} 				t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	nbr_meals;
	long	start_simulation;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}		t_table;

/* MAIN FUNCTIONS*/


/* UTILS FUNCTIONS */
void	error_exit(const char *error_msg);

/* PARSING FUNCTIONS */
void 	parse_input(char **argv, t_table *table);

#endif
