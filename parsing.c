/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/22 01:28:41 by abdennac         ###   ########.fr       */
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
		return (printf("No negative numbers pls\n"), NULL);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (printf("input is not a digit\n"), NULL);
	number = str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		len++;
	}
	if (len > 10)
		return (printf("value too long\n"), NULL);
	return (number);
}

size_t ft_atoi(const char *str, t_table *table)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	str = is_valid(str);
	if (!str)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > 2147483647)
	{
		printf("value too big\n");
		table->error = true;
	}
	return (res);
} 

int check(t_table *table, char **av)
{	
	table->philo_count = ft_atoi(av[1], table);
	if (table->error == true)
		return (1);
	table->time_to_die = ft_atoi(av[2], table);
	if (table->error == true)
		return (1);
	table->time_to_eat = ft_atoi(av[3], table);
	if (table->error == true)
		return (1);
	table->time_to_sleep = ft_atoi(av[4], table);
	if (table->error == true)
		return (1);
	if (av[5])
	{
		table->meals_limit = ft_atoi(av[5], table);
		if (table->error == true)
			return (1);
	}
	else
		table->meals_limit = -1;
	return (0);
}
