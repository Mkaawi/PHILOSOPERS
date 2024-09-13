/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:04:03 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/08 01:29:21 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	size_t			meals_counter;
	size_t			last_meal_time; 	// time passed fom last meal
	int				full; 				//flag if philo eaten all meals
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_table			*table;
} t_philo;

typedef struct s_table
{
	size_t			philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meals_limit; 		// both flag and value
	size_t			start_time;
	int				end_simulation; 	// flag if a philo dies / all full
	t_philo			*philos;
} t_table;


void		check(t_table	*table, char **av);
void		table_init(t_table	*table);
// void		start_sim(t_table	*table);
void		*pmalloc(int bytes);
size_t	timestamp(void);
void	*philo_life(void *philo);
void		error(char *str);

#endif

// int *dead;
// pthread_mutex_t write_lock;
// pthread_mutex_t dead_lock;
// pthread_mutex_t meal_lock;