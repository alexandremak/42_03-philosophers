/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:56:07 by amak              #+#    #+#             */
/*   Updated: 2024/01/02 21:14:37 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_dead(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	elapsed = gettime(MILISECONDS) - get_long(&philo->mutex, 
				&philo->last_meal_time);
	time_to_die = philo->table->time_die / 1000;
	if (get_bool(&philo->mutex, &philo->full))
		return (0);
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

void	*monitor_dinner(void *data)
{
	t_table 	*table;
	int			i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, 
			&table->nbr_threads_running, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_dead(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return NULL;
}
