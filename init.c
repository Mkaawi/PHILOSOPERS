/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:48:44 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/08 01:29:12 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_init(t_table *table)
{
	size_t i;

	table->start_time = timestamp();
	i = -1;
	while (++i < table->philo_count)
	{
		// Initialize philosopher data
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_time = 0;
		table->philos[i].meals_counter = 0;
		table->philos[i].full = 0;
		table->philos[i].table = table;

		pthread_mutex_init(table->philos[i].left_fork, NULL);

		if (i == table->philo_count - 1)
			table->philos[i].right_fork = table->philos[0].left_fork;
		else
			table->philos[i].right_fork = table->philos[i + 1].left_fork;
		pthread_create(&table->philos[i].thread_id, NULL, &philo_life, &table->philos[i]);
	}

	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philos[i].thread_id, NULL);

	return (0);
}

void table_init(t_table *table)
{
	table->end_simulation = -1;
	table->philos = pmalloc(sizeof(table->philos) * table->philo_count);
}