/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:45:59 by aait-bou          #+#    #+#             */
/*   Updated: 2025/01/07 22:37:12 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_threads_are_running(atomic_long *threads, long thread_nbr)
{
	bool	ret;

	ret = false;
	if (*threads == thread_nbr)
		ret = true;
	return (ret);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;

	elapsed = get_time_milli() - philo->last_meal_time;
	if (elapsed >= (philo->table->time_to_die))
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_are_running(&table->threads_running_count,
			table->philo_number))
		continue ;
	while (!table->end_of_simulation)
	{
		i = 0;
		while (i < table->philo_number && !table->end_of_simulation)
		{
			if (philo_died(&table->philos[i]))
			{
				table->end_of_simulation = true;
				print_status(DIED, &table->philos[i]);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
