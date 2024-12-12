/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:11 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/12 10:04:21 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_table(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->stop_lock);
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		pthread_mutex_destroy(&table->philos[i].left_fork);
		pthread_mutex_destroy(&table->philos[i].count_lock);
	}
	free(table->philos);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 6 && ac != 5)
		return (printf("invalid number of arguments\n"), 1);
	if (table_init(&table, av) == 1)
		return (1);
	philo_init(&table);
	clean_table(&table);
	return (0);
}
