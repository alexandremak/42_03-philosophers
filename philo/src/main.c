/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:52 by amak              #+#    #+#             */
/*   Updated: 2024/01/19 21:50:18 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments!\n");
		return (1);
	}
	if (!valid_input(argc, argv))
	{
		printf("Arguments with invalid values inserted!\n");
		return (1);
	}
	parse_input(&table, argv);
	if (!init_table(&table))
	{
		printf("Error initializing table values!\n");
		return (1);
	}
	init_dinner(&table);
	clean_table(&table);
	return (0);
}
