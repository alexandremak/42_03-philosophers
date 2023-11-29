/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 02:38:38 by amak              #+#    #+#             */
/*   Updated: 2023/11/29 00:56:19 by amak             ###   ########.fr       */
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
		table_init(&table);
		// start_simulation(&table);
		// free_all(&table);
		print_table(&table);
	}
}
