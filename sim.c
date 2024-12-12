/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:34:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/12 08:39:25 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philos(void *arg)
{
	t_table		*table;
	long int	time_since_last_meal;
	int			i;

	table = (t_table *)arg;
	t_philo	*philos;
	philos = table->philos;
	while (!table->end_simulation)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			time_since_last_meal = timestamp() - philos[i].last_meal_time;
			pthread_mutex_unlock(&philos[i].meal_lock);
			if (time_since_last_meal >= table->time_to_die)
			{
				is_dead(&philos[i], 1);
				// pthread_mutex_lock(&table->dead_lock);
				// table->end_simulation = 1;
				// pthread_mutex_unlock(&table->dead_lock);
				pthread_mutex_lock(&table->write_lock);
				printf("%ld : philo %d died\n", timestamp() - table->start_time, philos[i].id);
				pthread_mutex_unlock(&table->write_lock);
				return (NULL);
			}
			usleep(200);
		}
	}
	return (NULL);
}

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print(philo, "has taken a fork\n");
	if (philo->table->philo_count == 1)
	{
		ft_usleep(philo->table->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork\n");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = timestamp();
	pthread_mutex_unlock(&philo->meal_lock);
	philo->meals_counter++;
	print(philo, "is eating\n");
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	print(philo, "is sleeping\n");
	ft_usleep(philo->table->time_to_sleep);
	print(philo, "is thinking\n");
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 5);
	while (!is_dead(philo, 0))
	{
		pick_fork(philo);
		eat(philo);
		if (philo->meals_counter >= philo->table->meals_limit && philo->table->meals_limit != -1)
		{
	        print(philo, "is full*********************\n");
			pthread_mutex_lock(&philo->table->stop_lock);
			if (++philo->table->finshed_eating == philo->table->philo_count)
				is_dead(philo, 1);
			pthread_mutex_unlock(&philo->table->stop_lock);
			return (NULL);
		}
	}
	return (NULL);
}
