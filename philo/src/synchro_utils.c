/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 22:04:02 by amak              #+#    #+#             */
/*   Updated: 2024/01/04 22:26:55 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

void	increase_unit(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

int	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	int	res;
	
	res = 0;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		res = 1;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}
