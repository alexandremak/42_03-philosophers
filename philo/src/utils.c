/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:30:35 by amak              #+#    #+#             */
/*   Updated: 2024/01/02 21:38:37 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error_msg)
{
	printf("%s", error_msg);
	exit(EXIT_FAILURE);
}

/* Microseconds from Midnight (0 hour), January 1, 1970 */
long	gettime(t_time_code time_code)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("Function getitmeofday() failed.");
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + (tv.tv_usec));
	else
		error_exit("Wrong input to gettime function.");
	return (0);
}

void	ft_sleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while ((gettime(MICROSECONDS) - start) < usec)
				;
	}
}
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;
	
	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->mutex, DESTROY);
	}
	safe_mutex_handle(&table->table_mutex, DESTROY);
	safe_mutex_handle(&table->write_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
