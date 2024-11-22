/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 23:50:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/22 01:24:50 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *str)
{
	printf("%s\n", str);
	// exit(1);
}

void	*pmalloc(int bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		error("malloc error");
	return (ptr);
}

size_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(size_t ms)
{
    size_t end_time;
	
    end_time = timestamp() + ms;
    while (timestamp() < end_time)
        usleep(100); 
}

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (nb)
		philo->table->end_simulation = 1;
	if (philo->table->end_simulation)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
        printf("philo is dead\n"); 
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (0); 
}

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->table->write_lock));
	time = timestamp() - philo->table->start_time;
	if (!philo->table->end_simulation && time >= 0
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%ld %d %s", timestamp() - philo->table->start_time, philo->id, str);
	pthread_mutex_unlock(&(philo->table->write_lock));
}
