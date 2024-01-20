/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:40:41 by amak              #+#    #+#             */
/*   Updated: 2024/01/17 21:52:25 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_int(&table->read_mutex, &table->all_threads_ready))
		;
}

int	all_threads_running(t_mutex *mutex, int *threads, int philos_nbr)
{
	int	res;

	res = 0;
	pthread_mutex_lock(mutex);
	if (*threads == philos_nbr)
		res = 1;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	dinner_ended(t_table *table)
{
	return (get_int(&table->read_mutex, &table->end_dinner));
}
