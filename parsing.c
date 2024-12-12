/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/12 10:16:43 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	is_valid(const char *str)
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
		return (printf("No negative numbers pls\n"), 0);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (printf("input is not a digit\n"), 0);
	number = str;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		len++;
	}
	if (len > 10)
		return (printf("value too long\n"), 0);
	return (1);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!is_valid(str[i]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
