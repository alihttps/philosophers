/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:45:45 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 22:41:43 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*loner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time_milli();
	philo->table->threads_running_count++;
	philo->table->start_of_simulation = get_time_milli();
	print_status(TAKE_FIRST_FORK, philo);
	while (!philo->table->end_of_simulation)
		usleep(200);
	return (NULL);
}

void	think(t_philo *philo)
{
	long	t_think;

	print_status(THINKING, philo);
	if (philo->table->philo_number % 2 == 0)
		return ;
	t_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.5, philo->table);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(TAKE_SECOND_FORK, philo);
	philo->last_meal_time = get_time_milli();
	if (!philo->table->end_of_simulation)
	{
		philo->meal_counter++;
	}
	print_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_of_meals > 0
		&& philo->meal_counter == philo->table->num_of_meals)
	{
		philo->full = true;
	}
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time_milli();
	philo->table->threads_running_count++;
	de_synchronise(philo);
	while (1)
	{
		if (philo->full)
			return (NULL);
		eat(philo);
		print_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
		if (philo->table->end_of_simulation)
			return (NULL);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	table->start_of_simulation = get_time_milli();
	if (table->num_of_meals == 0)
		return ;
	else if (table->philo_number == 1)
		pthread_create(&table->philos[0].thread_id, NULL, loner,
			&table->philos[0]);
	else
	{
		while (i < table->philo_number)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
				&table->philos[i]);
			i++;
		}
	}
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	table->ready_to_sync = true;
	i = 0;
	while (i < table->philo_number)
		pthread_join(table->philos[i++].thread_id, NULL);
	pthread_join(table->monitor, NULL);
	table->end_of_simulation = true;
}
