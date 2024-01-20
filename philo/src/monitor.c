/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:21:22 by amak              #+#    #+#             */
/*   Updated: 2024/01/20 16:22:15 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_dead(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	elapsed = gettime() - get_long(&philo->mutex, &philo->time_last_meal);
	time_to_die = philo->table->time_die;
	if (get_int(&philo->mutex, &philo->full))
		return (0);
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->read_mutex,
			&table->nbr_threads_running, table->nbr_philos))
		usleep(200);
	while (!dinner_ended(table))
	{
		i = -1;
		while (++i < table->nbr_philos && !dinner_ended(table))
		{
			if (philo_dead(table->philos + i))
			{
				set_int(&table->read_mutex, &table->end_dinner, 1);
				write_status(table->philos + i, DIED);
			}
		}
	}
	return (NULL);
}
