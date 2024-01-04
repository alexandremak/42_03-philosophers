/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:59:44 by amak              #+#    #+#             */
/*   Updated: 2024/01/04 22:21:59 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->mutex, LOCK);
	write_status(TAKE_FIST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->mutex, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->mutex, &philo->last_meal_time, gettime(MILISECONDS));
	philo->nr_meals++;
	write_status(EATING, philo);
	ft_sleep(philo->table->time_eat, philo->table);
	if (philo->table->nbr_meals > 0 
		&& philo->nr_meals == philo->table->nbr_meals)
		set_bool(&philo->mutex, &philo->full, 1);
	safe_mutex_handle(&philo->first_fork->mutex, UNLOCK);
	safe_mutex_handle(&philo->second_fork->mutex, UNLOCK);	
}

static void	think(t_philo *philo)
{
	write_status(THINKING, philo);
}

void	*dinner_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->mutex, &philo->last_meal_time, gettime(MILISECONDS));
	increase_unit(&philo->table->table_mutex, &philo->table->nbr_threads_running);
	write_status(TAKE_FIST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);	
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->mutex, &philo->last_meal_time, gettime(MILISECONDS));
	increase_unit(&philo->table->table_mutex, &philo->table->nbr_threads_running);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_sleep(philo->table->time_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_meals == 0)
		return;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, dinner_alone,
							&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, 
								&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE); 
	table->start_simulation = gettime(MILISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, 1);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
