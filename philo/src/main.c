/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 02:38:38 by amak              #+#    #+#             */
/*   Updated: 2024/01/01 20:38:41 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc < 5 || argc > 6)
		error_exit("Invalid number of arguments!\n");
	else
	{
		parse_input(&table, argv);
		print_table(&table);
		table_init(&table);
		dinner_start(&table);
		// free_all(&table);
	}
}
