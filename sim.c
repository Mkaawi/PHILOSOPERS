/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:34:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/09 08:06:13 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_philos(void *arg)
{
	t_table		*table;
	long int	time_since_last_meal;
	int			i;

	table = (t_table *)arg;
	while (!table->end_simulation)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			pthread_mutex_lock(&table->meal_lock);
			time_since_last_meal = timestamp() - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->meal_lock);
			if (time_since_last_meal >= table->time_to_die)
			{
				pthread_mutex_lock(&table->write_lock);
				printf("%ld : philo %d died\n", timestamp() - table->start_time, table->philos[i].id);
				pthread_mutex_unlock(&table->write_lock);
				pthread_mutex_lock(&table->dead_lock);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->dead_lock);
				return (NULL);
			}
		}
		// ft_usleep(1000);
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
	print(philo, "is eating\n");
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = timestamp();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_lock);
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
		if (philo->meals_counter >= philo->table->meals_limit
			&& philo->table->meals_limit != -1)
		{
			pthread_mutex_lock(&philo->table->stop_lock);
			printf("philo count : %ld $$$$$$$$$$$$$\n", philo->table->philo_count);
			printf("end sim : %d $$$$$$$$$$$$$\n", philo->table->end_simulation);
			printf("meals limit : %ld $$$$$$$$$$$$$\n", philo->table->meals_limit);
			printf("\nfinished : %d ###############\n\n", philo->table->finshed_eating);
			if (++philo->table->finshed_eating == philo->table->philo_count)
            {
	        	print(philo, "is full ****************************\n");
				is_dead(philo, 1);
            }
			pthread_mutex_unlock(&philo->table->stop_lock);
			return (NULL);
		}
	}
	return (NULL);
}
