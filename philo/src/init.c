/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:19:22 by amak              #+#    #+#             */
/*   Updated: 2023/11/29 00:49:23 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* 	the odd number philosophers begin taking the left fork first and the right 
	fork second, but the even ones begin with the right fork and then the left
	fork. */
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	
	if (philo->id % 2 != 0)
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	else
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
		
}

static void	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals = 0;
		table->philos[i].full = 0;
		table->philos[i].table = table;
		assign_forks(table->philos, table->forks, i);
		i++;
	}
}

void 	table_init(t_table *table)
{
	int 	i;
	
	i = 0;
	table->end_simulation = 0;
	table->philos = safe_malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = safe_malloc(table->philo_nbr * sizeof(t_fork));
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].mutex, INIT);
		table->forks[i].id = i;
		i++;
	}
	philo_init(table);
	
}