/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:28:12 by amak              #+#    #+#             */
/*   Updated: 2024/01/23 18:56:19 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void	ft_sleep(long useconds, t_table *table)
{
	long	start;

	start = gettime();
	while ((gettime() - start) < useconds)
	{
		if (dinner_ended(table))
			break ;
		usleep(100);
	}
}

void	clean_table(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = table->philos + i;
		fork = table->forks + i;
		pthread_mutex_destroy(&philo->mutex);
		pthread_mutex_destroy(&fork->mutex);
		i++;
	}
	pthread_mutex_destroy(&table->read_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	free(table->forks);
	free(table->philos);
}
