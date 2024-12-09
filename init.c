/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 00:48:44 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/09 03:42:34 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_init(t_table *table)
{
	long int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_time = timestamp();
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].left_fork, NULL);
		if (i == table->philo_count - 1)
			table->philos[i].right_fork = &table->philos[0].left_fork;
		else
			table->philos[i].right_fork = &table->philos[i + 1].left_fork;
		pthread_create(&table->philos[i].thread_id, NULL, &philo_life,
			&table->philos[i]);
	}
	pthread_create(&table->monitor_thread, NULL, &monitor_philos, table);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(table->monitor_thread, NULL);
	return (0);
}

int	table_init(t_table *table, char **av)
{
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->stop_lock, NULL);
	if (check_num(av))
		return (printf("Invalid Arguments\n"), 1);
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_limit = ft_atoi(av[5]);
	else
		table->meals_limit = -1;
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (table->philos == NULL)
		return (1);
	table->start_time = timestamp();
	table->finshed_eating = 0;
	table->end_simulation = 0;
	return (0);
}
