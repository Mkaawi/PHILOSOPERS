/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 23:50:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/12 10:14:57 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(size_t ms)
{
	size_t	end_time;

	end_time = timestamp() + ms;
	while (timestamp() < end_time)
		usleep(100);
}

int	is_dead(t_philo *philo, int set_end)
{
	if (set_end)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->table->end_simulation = 1;
		pthread_mutex_unlock(&philo->table->dead_lock);
	}
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->end_simulation)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (0);
}

void	print(t_philo *philo, char *str)
{
	long int	time;
	int			val;

	pthread_mutex_lock(&(philo->table->write_lock));
	pthread_mutex_lock(&(philo->table->dead_lock));
	val = philo->table->end_simulation;
	pthread_mutex_unlock(&(philo->table->dead_lock));
	if (!val)
	{
		time = timestamp() - philo->table->start_time;
		if (time >= 0 && time <= INT_MAX)
			printf("%ld %d %s", time, philo->id, str);
	}
	pthread_mutex_unlock(&(philo->table->write_lock));
}

int	get_end_value(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->dead_lock);
	value = table->end_simulation;
	pthread_mutex_unlock(&table->dead_lock);
	return (value);
}
