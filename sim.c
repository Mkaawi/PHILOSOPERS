#include "philosophers.h"

void eat(t_philo *philo)
{
	printf("philo is eating\n");
	philo->last_meal_time = timestamp();
	printf("philo->last_meal_time : %ld\n", philo->last_meal_time);
	philo->meals_counter++;
}

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->table->time_to_die + 1);
	pthread_mutex_lock(&philo->table->meal_lock);
	pthread_mutex_lock(&philo->table->dead_lock);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_meal_time >= (size_t)(philo->table->time_to_die))
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		pthread_mutex_unlock(&philo->table->dead_lock);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (NULL);
}

void pick_fork(t_philo philo)
{
	pthread_mutex_lock(&philo.left_fork);
	printf("picked l fork\n");

	pthread_mutex_lock(&philo.right_fork);
	printf("picked r fork\n");
}

void *philo_life(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;

	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 10);
	while(!is_dead(philo, 0))
	{
		pick_fork(*philo);
		eat(philo);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		ft_usleep(philo->table->time_to_sleep);
		printf("philo is sleeping\n");
	}
	return 0;
}

// void	*philo_life(void *phi)
// {
// 	t_philo		*philo;
// 	pthread_t	t;

// 	philo = (t_philo *)phi;
// 	while (!is_dead(philo, 0))
// 	{
// 		pthread_create(&t, NULL, check_death, phi);
// 		take_fork(philo);
// 		philo_eat(philo);
// 		pthread_detach(t);
// 		if (philo->m_count == philo->table->n_eat)
// 		{
// 			pthread_mutex_lock(&philo->table->dead_lock);
// 			if (++philo->table->philo_eat == philo->table->n_philo)
// 			{
// 				pthread_mutex_unlock(&philo->table->dead_lock);
// 				is_dead(philo, 2);
// 			}
// 			pthread_mutex_unlock(&philo->table->dead_lock);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }