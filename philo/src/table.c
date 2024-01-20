/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:52:41 by amak              #+#    #+#             */
/*   Updated: 2024/01/17 22:09:07 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].mutex, NULL))
			return (0);
		i++;
	}
	return (1);
}

/*	The even id philosophers and the last one begins taking the right fork and 
	the then the left fork, the odd philosophers begins with the left fork 
	and then the righ fork. */
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	nbr_philos;

	nbr_philos = philo->table->nbr_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % nbr_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % nbr_philos];
		philo->second_fork = &forks[philo_position];
	}
}

static int	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_ate = 0;
		philo->full = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->mutex, NULL))
			return (0);
		assign_forks(philo, table->forks, i);
		i++;
	}
	return (1);
}

int	init_table(t_table *table)
{
	table->end_dinner = 0;
	table->all_threads_ready = 0;
	table->nbr_threads_running = 0;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (table->philos == NULL || table->forks == NULL 
		|| pthread_mutex_init(&table->read_mutex, NULL)
		|| pthread_mutex_init(&table->write_mutex, NULL))
		return (0);
	if (!init_forks(table) || !init_philos(table))
		return (0);
	return (1);
}
