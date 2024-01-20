/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:31:24 by amak              #+#    #+#             */
/*   Updated: 2024/01/17 21:35:12 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_int(t_mutex *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

int	get_int(t_mutex *mutex, int *value)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	int_increase(t_mutex *mutex, int *dest)
{
	pthread_mutex_lock(mutex);
	(*dest)++;
	pthread_mutex_unlock(mutex);
}
