/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:45:52 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 22:28:19 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philo, t_fork *fork, int position)
{
	philo->first_fork = &fork[position];
	philo->second_fork = &fork[(position + 1) % philo->table->philo_number];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[(position + 1) % philo->table->philo_number];
		philo->second_fork = &fork[position];
	}
}

void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_counter = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_table(t_table *table)
{
	int	i;

	table->end_of_simulation = false;
	table->ready_to_sync = false;
	table->threads_running_count = 0;
	table->full_count = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(t_fork) * table->philo_number);
	if (!table->forks)
		return ;
	i = 0;
	while (i < table->philo_number)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].id = i;
		i++;
	}
	init_philo(table);
}

void	fill_table(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) < 0)
		{
			printf("not a valid value\n");
			return ;
		}
		i++;
	}
	table->philo_number = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->num_of_meals = atol(av[5]);
	else
		table->num_of_meals = -1;
}
