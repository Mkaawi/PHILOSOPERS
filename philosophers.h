/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:03 by abdennac          #+#    #+#             */
/*   Updated: 2024/12/12 10:05:37 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	int					meals_counter;
	long int			last_meal_time;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		count_lock;
}						t_philo;

typedef struct s_table
{
	pthread_t			monitor_thread;
	long int			philo_count;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			meals_limit;
	long int			start_time;
	int					end_simulation;
	int					finshed_eating;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		stop_lock;
	t_philo				*philos;
	bool				error;
}						t_table;

int						table_init(t_table *table, char **av);
int						philo_init(t_table *table);
void					*philo_life(void *philo);
int						ft_atoi(const char *str);
int						check_num(char **str);
int						ft_isdigit(int c);
void					*monitor_philos(void *arg);
size_t					timestamp(void);
int						is_dead(t_philo *philo, int nb);
void					ft_usleep(size_t ms);
void					print(t_philo *philo, char *str);

#endif
