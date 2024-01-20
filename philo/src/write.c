/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:18:40 by amak              #+#    #+#             */
/*   Updated: 2024/01/17 22:03:13 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	write_status(t_philo *philo, t_action action)
{
	long	elapsed;

	elapsed = (gettime() - philo->table->time_start_dinner) / 1000;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK)
		&& !dinner_ended(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (action == EATING && !dinner_ended(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (action == SLEEPING && !dinner_ended(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (action == THINKING && !dinner_ended(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (action == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
