/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:03:43 by amak              #+#    #+#             */
/*   Updated: 2024/01/23 18:31:49 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*	Initial check if the string is composed with a '+' and only with numbers 
	with a lengh until 10 digits because of MAX_INT total number of digits */
static	int	number_ok(char *str)
{
	int		len;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			str++;
			len++;
		}
		else
			return (0);
	}
	if (len == 0 || len > 10)
		return (0);
	return (1);
}

/*	The string contect is validated before so the conversion is always a
	positive number */
static long	ft_atol_positive(char *str)
{
	long	res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	while (*str)
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}

int	valid_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!number_ok(argv[i]))
			return (0);
		if (ft_atol_positive(argv[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

/*	The time is converted to microseconds so is multiplied for 1000. 
	The value -1 is used as a flag value when the number of meals is not
	inserted */
void	parse_input(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol_positive(argv[1]);
	table->time_die = ft_atol_positive(argv[2]) * 1000;
	table->time_eat = ft_atol_positive(argv[3]) * 1000;
	table->time_sleep = ft_atol_positive(argv[4]) * 1000;
	if (argv[5])
		table->nbr_meals = ft_atol_positive(argv[5]);
	else
		table->nbr_meals = -1;
}
