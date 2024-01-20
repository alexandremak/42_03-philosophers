/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:56:44 by amak              #+#    #+#             */
/*   Updated: 2024/01/20 16:59:13 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->mutex, &philo->time_last_meal, gettime());
	int_increase(&philo->table->read_mutex, &philo->table->nbr_threads_running);
	write_status(philo, TAKE_FIRST_FORK);
	while (!dinner_ended(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex);
	write_status(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(&philo->second_fork->mutex);
	write_status(philo, TAKE_SECOND_FORK);
	set_long(&philo->mutex, &philo->time_last_meal, gettime());
	philo->meals_ate++;
	write_status(philo, EATING);
	printf("Philo ID: %d AQUI!\n", philo->id);
	ft_sleep(philo->table->time_eat);
	if (philo->table->nbr_meals > 0 && 
		philo->meals_ate == philo->table->nbr_meals)
		set_int(&philo->mutex, &philo->full, 1);
	pthread_mutex_unlock(&philo->first_fork->mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
}

static void	think(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	time_to_eat = philo->table->time_eat;
	time_to_sleep = philo->table->time_sleep;
	time_to_think = (time_to_eat * 2) - time_to_sleep;
	write_status(philo, THINKING);
	if (philo->table->nbr_philos % 2 != 0 && time_to_think > 0)
		ft_sleep(time_to_think);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->mutex, &philo->time_last_meal, gettime());
	int_increase(&philo->table->read_mutex, &philo->table->nbr_threads_running);
	while (!dinner_ended(philo->table))
	{
		eat(philo);
		if (get_int(&philo->mutex, &philo->full))
		{
			write_status(philo, THINKING);	
			break;
		}
		write_status(philo, SLEEPING);
		ft_sleep(philo->table->time_sleep);
		think(philo);
	}
	return (NULL);
}

void	init_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_meals == 0)
		return ;
	else if (table->nbr_philos == 1)
		pthread_create(&table->philos[0].thread_id, NULL, &routine_alone, 
			&table->philos[0]);
	else
	{
		while (++i < table->nbr_philos)
			pthread_create(&table->philos[i].thread_id, NULL, &routine,
				&table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, &monitor_dinner, table);
	table->time_start_dinner = gettime();
	set_int(&table->read_mutex, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philos[i].thread_id, NULL);
	set_int(&table->read_mutex, &table->end_dinner, 1);
	pthread_join(table->monitor, NULL);
}
