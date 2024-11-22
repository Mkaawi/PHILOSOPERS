/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:11 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/22 01:29:43 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_table(t_table	*table)
{
	(void)table;
}

int main (int ac, char **av)
{
	t_table	table;

	if (ac != 6 && ac != 5)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	if (check(&table, av) == 1)
		return (1);
	// table_init(&table);
	// philo_init(&table);
	// clean_table(&table); //if a philo dies or all are full
}
