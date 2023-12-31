/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:50:10 by amak              #+#    #+#             */
/*   Updated: 2024/01/01 20:33:50 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_table(t_table *table)
{
	printf("\nNumber of philosophers: %ld\n", table->philo_nbr);
	printf("Time to die: %ld ms\n", table->time_die / 1000);
	printf("Time to eat: %ld ms\n", table->time_eat / 1000);
	printf("Time to sleep: %ld ms\n", table->time_sleep / 1000);
	printf("Number of meals must eat: %ld\n\n", table->nbr_meals);
}