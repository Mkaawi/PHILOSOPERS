/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:11 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/08 00:49:45 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_sim(t_table	*table)
{
	(void)table;
}

void	clean_table(t_table	*table)
{
	(void)table;
}

int main (int ac, char **av)
{
	t_table	table;
	
	if (ac != 6 && ac != 5)
		error("invalid number of arguments");
	check(&table, av);
	table_init(&table);
	// start_sim(&table);
	// clean_table(&table); //if a philo dies or all are full
}