/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/08 00:48:57 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static const char *is_valid(const char *str)
{
	int			i;
	int			len;
	const char	*number;

	i = 0;
	len = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error("No negative numbers pls");
	if (!(str[i] >= '0' && str[i] <= '9'))
		error("input is not a digit");
	number = str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		len++;
	}
	if (len > 10)
		error("value too long");
	return (number);
}

static size_t ft_atoi(const char *str)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	str = is_valid(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > 2147483647)
		error("value too big");
	return (res);
}

void check(t_table *table, char **av)
{
	// res is multiplied by 1000 to convert from ms to usec for usleep
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000 ||
		table->time_to_sleep < 60000)
		error("value too low, use bigger than 60ms");
	if (av[5])
		table->meals_limit = ft_atoi(av[5]);
	else
		table->meals_limit = -1;
}
