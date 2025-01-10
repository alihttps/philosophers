/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:46:06 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/10 19:48:15 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef enum e_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DIED,
}						t_status;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		fork;

}						t_fork;

typedef struct s_philo
{
	atomic_int			id;
	atomic_long			meal_counter;
	atomic_bool			full;
	atomic_long			last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_table				*table;

}						t_philo;

typedef struct s_table
{
	atomic_long			full_count;
	atomic_long			num_of_meals;
	atomic_long			philo_number;
	atomic_long			time_to_die;
	atomic_long			time_to_eat;
	atomic_long			time_to_sleep;
	atomic_long			start_of_simulation;
	atomic_bool			ready_to_sync;
	atomic_bool			end_of_simulation;
	atomic_long			threads_running_count;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;

}						t_table;

void					parse_input(char **av);

void					fill_table(t_table *table, char **av);

void					init_table(t_table *table);

void					start_dinner(t_table *table);

void					de_synchronise(t_philo *philo);

void					wait_all_threads(t_table *table);

void					think(t_philo *philo);

long					get_time_sec(void);

long					get_time_milli(void);

void					print_status(t_status stat, t_philo *philo);

long					ft_atol(char *av);

void					*monitor_dinner(void *data);

int						precise_usleep(size_t milliseconds, t_table *table);

bool					valid_input(int ac, char **av);

#endif