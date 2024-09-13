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

void	*philo_life(void *philo)
{
	(void)philo;
	return 0;
}

int main (int ac, char **av)
{
	t_table	table;
	
	if (ac != 6 && ac != 5)
		error("invalid number of arguments");
	check(&table, av);

	//****************** printing
	printf("philo count is : %ld\n", table.philo_count);
	printf("time_to_die is : %ld\n", table.time_to_die);
	printf("time_to_eat is : %ld\n", table.time_to_eat);
	printf("time_to_sleep is : %ld\n", table.time_to_sleep);
	if (table.meals_limit)
	printf("meal limit is : %ld\n", table.meals_limit);
	//******************

	table_init(&table);
	philo_init(&table);


	// start_sim(&table);
	// clean_table(&table); //if a philo dies or all are full
}
