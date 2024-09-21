/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:34:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/20 07:39:43 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philosophers.h"

void pick_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	printf("Philosopher %d picked left fork\n", philo->id);
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return;
	}
	pthread_mutex_lock(&philo->right_fork);
	printf("Philosopher %d picked right fork\n", philo->id);
}

void eat(t_philo *philo)
{
	printf("Philosopher %d is eating\n", philo->id);
	philo->last_meal_time = timestamp();
	philo->meals_counter++;
	ft_usleep(philo->table->time_to_eat);
}

void *check_death(void *phi)
{
	t_philo *philo = (t_philo *)phi;
	while (!is_dead(philo, 0))
	{
		ft_usleep(philo->table->time_to_die / 2);
		pthread_mutex_lock(&philo->table->meal_lock);
		if (!is_dead(philo, 0) && timestamp() - philo->last_meal_time >= philo->table->time_to_die)
		{
			pthread_mutex_unlock(&philo->table->meal_lock);
			print(philo, " died\n");
			is_dead(philo, 1);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->meal_lock);
	}
	return (NULL);
}

void *philo_life(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	pthread_t t;

	pthread_create(&t, NULL, check_death, philo);
	pthread_detach(t);

	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 5); 

	while (!is_dead(philo, 0))
	{
		pick_fork(philo);
		if (is_dead(philo, 0))
			break;
		eat(philo);
		if (philo->meals_counter >= philo->table->meals_limit)
		{
			printf("Philosopher %d is full\n", philo->id);
			break;
		}
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		printf("Philosopher %d is sleeping\n", philo->id);
		ft_usleep(philo->table->time_to_sleep);
	}
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return NULL;
}
