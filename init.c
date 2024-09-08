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

void table_init(t_table *table)
{
	table->end_simulation = -1;
	table->philosophers = pmalloc(table->philo_count);
	
}