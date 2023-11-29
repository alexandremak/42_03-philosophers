/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:39:50 by amak              #+#    #+#             */
/*   Updated: 2023/11/28 22:07:48 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/* Checks if the input is number, an INT (<INT MAX) and not negative */
static const char *valid_input(const char *str)
{
	int 		len;
	const char *number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only positive numbers allowed!\n");
	if (!is_number(*str))
		error_exit("Only numbers as arguments allowed!\n");
	number = str;
	while (is_number(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		error_exit("Argument number is bigger then INT_MAX!\n");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	result;
	
	result = 0;
	str = valid_input(str);
	while (is_number(*str))
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	if (result > INT_MAX)
		error_exit("Argument number is bigger then INT_MAX!\n");
	return (result);
}

/* The input time to die, eat and sleep is miliseconds and usleep function
	is in microseconds, so we have to convert multiplying for 1000. */
void parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]) * 1000;
	table->time_eat = ft_atol(argv[3]) * 1000;
	table->time_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->nbr_meals = ft_atol(argv[5]);
	else
		table->nbr_meals = -1;
}
